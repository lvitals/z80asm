#ifndef _FILES_H_
#define _FILES_H_

#include <stdio.h>

/* defines which are not function-specific */
#ifndef BUFLEN
#define BUFLEN 300 /* size of readbuffer for file i/o */
#endif

/* filetypes that can appear on the input. object files are on the todo list */
enum filetype
{
  FILETYPE_ASM
};

/* files that were given on the commandline */
struct infile
{
  int name;
  enum filetype type;
};

/* filenames must be remembered for references */
struct name
{
  struct name *next, *prev;
  int name;
};

/* the include path */
struct includedir
{
  struct includedir *next;
  int name;
};

/* files */
extern FILE *realoutputfile, *outfile, *reallistfile, *listfile, *labelfile;
extern const char *realoutputfilename;
extern const char *labelfilename;
extern struct infile *infile;

extern struct includedir *firstincludedir;

/* prefix for labels in labelfile */
extern const char *labelprefix;

/* bools to see if files are opened */
extern int havelist, label;

/* number of infiles in array */
extern int infilecount;

/* callback function for argument parser, used to open output files. */
FILE *
openfile(int *done,          /* flag to check that a file is opened only once. */
         const char *type,   /* name of filetype for error message */
         FILE *def,          /* default value, in case "-" is specified */
         const char *name,   /* filename to open */
         const char *flags); /* open flags */

/* open an included file, searching the path */
FILE *
open_include_file(const char *name, struct includedir **dir,
                  const char *flags);

/* queue a file to be opened for reading */
void open_infile(const char *name);

/* add a directory to the include search path */
void add_include(const char *name);

void try_use_real_file(FILE *real, FILE **backup);

void flush_to_real_file(FILE *real, FILE *tmp);

#endif
