#include "files.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <unistd.h>

#include "error.h"
#include "stringstore.h"

/* files */
FILE *realoutputfile, *outfile, *reallistfile, *listfile, *labelfile;
const char *realoutputfilename;
const char *labelfilename;
struct infile *infile;

/* prefix for labels in labelfile */
const char *labelprefix = "";

/* bools to see if files are opened */
int havelist = 0, label = 0;

/* callback function for argument parser, used to open output files. */
FILE *
openfile(int *done,         /* flag to check that a file is opened only once. */
         const char *type,  /* name of filetype for error message */
         FILE *def,         /* default value, in case "-" is specified */
         const char *name,  /* filename to open */
         const char *flags) /* open flags */
{
  FILE *retval;
  if (*done)
  {
    fprintf(stderr, "Error: more than one %s specified\n", type);
    exit(1);
  }
  *done = 1;
  if (def && (!name || (name[0] == '-' && name[1] == 0)))
  {
    return def;
  }
  if (!name || !name[0])
  {
    fprintf(stderr, "Error: no %s specified\n", type);
    exit(1);
  }
  if (!(retval = fopen(name, flags)))
  {
    fprintf(stderr, "Unable to open %s %s: %s\n",
            type, name, strerror(errno));
    exit(1);
  }
  return retval;
}

/* open an included file, searching the path */
FILE *
open_include_file(const char *name, struct includedir **dir,
                  const char *flags)
{
  FILE *result;
  struct includedir *i;
  /* always try the current directory first */
  result = fopen(name, flags);
  if (result)
  {
    if (dir)
      *dir = NULL;
    return result;
  }
  for (i = firstincludedir; i != NULL; i = i->next)
  {
    const char *ipath = stringstore_get(i->name);
    char *tmp = malloc(strlen(ipath) + strlen(name) + 1);
    if (!tmp)
    {
      printerr(1, "not enough memory trying to open include file\n");
      return NULL;
    }
    strcpy(tmp, ipath);
    strcat(tmp, name);
    result = fopen(tmp, flags);
    free(tmp);
    if (result)
    {
      if (dir)
        *dir = i;
      return result;
    }
  }
  return NULL;
}

/* queue a file to be opened for reading */
void open_infile(const char *name)
{
  infile = realloc(infile, sizeof(struct infile) * (infilecount + 1));
  if (!infile)
  {
    fprintf(stderr, "Error: insufficient memory\n");
    exit(1);
  }
  /* only asm is currently supported */
  infile[infilecount].type = FILETYPE_ASM;
  infile[infilecount].name = stringstore_add(name, strlen(name));
  if (verbose >= 5)
    fprintf(stderr, "queued inputfile %s\n", name);
  infilecount++;
}

/* add a directory to the include search path */
void add_include(const char *name)
{
  struct includedir *i;
  char *tmp = malloc(strlen(name) + 1);

  i = malloc(sizeof(struct includedir));
  if (!i)
  {
    fprintf(stderr, "Error: insufficient memory\n");
    exit(1);
  }
  strcpy(tmp, name);
  if (name[strlen(name) - 1] != '/')
    strcat(tmp, "/");

  i->name = stringstore_add(tmp, strlen(tmp));

  i->next = firstincludedir;
  firstincludedir = i;
}

void try_use_real_file(FILE *real, FILE **backup)
{
  fpos_t pos;
  if (fgetpos(real, &pos) == 0)
  {
    *backup = real;
    return;
  }
  if (!(*backup = tmpfile()))
  {
    fprintf(stderr, "Error: Unable to open temporary file: %s\n",
            strerror(errno));
    exit(1);
  }
}

void flush_to_real_file(FILE *real, FILE *tmp)
{
  int l, size, len = 0;
  char buf[BUFLEN];
  if (tmp == real)
  {
    return;
  }
  rewind(tmp);
  while (1)
  {
    clearerr(tmp);
    errno = 0;
    len = fread(buf, 1, BUFLEN, tmp);
    if (len == 0 && feof(tmp))
      break;
    if (len <= 0)
    {
      fprintf(stderr, "error reading temp file: %s\n", strerror(errno));
      exit(1);
    }
    l = 0;
    while (l < len)
    {
      clearerr(real);
      size = fwrite(&buf[l], 1, len - l, real);
      if (size <= 0)
      {
        fprintf(stderr, "error writing final file: %s\n",
                strerror(errno));
        exit(1);
      }
      l += size;
    }
  }
}
