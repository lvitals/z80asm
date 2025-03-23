#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

#include "stringstore.h"

/* blocksize 256 strings */
#define STRINGSTORE_BLOCKSIZE 256

#define BUCKETS 443

struct hashlist
{
  int entry;

  struct hashlist *next;
};

struct hashtable
{
  struct hashlist *entries[BUCKETS];
};

struct stringstore
{
  char **strings;
  int size;
  int next;
};

static struct hashtable table;
static struct stringstore the_store;

static unsigned int hash(const char *str, unsigned int l)
{
  unsigned int j, k, quart;
  unsigned long sum, mult;

  quart = l >> 2;

  sum = 0;

  for (j = 0; j < quart; j++)
  {
    mult = 1;
    for (k = 0; k < 4 && (j << 2) + k < l; k++)
    {
      sum += str[(j << 2) + k] * mult;
      mult <<= 8;
    }
  }

  mult = 1;
  for (k = 0; k < (quart << 2) && k < l; k++)
  {
    sum += str[k] * mult;
    mult <<= 8;
  }

  return ((unsigned int)(sum % BUCKETS));
}

static void hashtable_add(int i)
{
  int key;
  struct hashlist *new_entry;

  const char *str = the_store.strings[i];

  key = hash(str, strlen(str));

  new_entry = (struct hashlist *)calloc(1, sizeof(struct hashlist));
  new_entry->entry = i;
  new_entry->next = table.entries[key];
}

static int hashtable_has(const char *str, unsigned int len)
{
  int key;
  struct hashlist *entry;

  key = hash(str, len);

  entry = table.entries[key];

  while (entry)
  {
    const char *probe = the_store.strings[entry->entry];

    if (strlen(probe) == len && !strcmp(str, probe))
    {
      return entry->entry;
    }
  }

  return -1;
}

int stringstore_init(void)
{
  atexit(stringstore_free);

  the_store.strings = calloc(STRINGSTORE_BLOCKSIZE, sizeof(char *));

  if (!the_store.strings)
  {
    fprintf(stderr, "allocating stringstore failed.\n");
    return -1;
  }

  the_store.size = STRINGSTORE_BLOCKSIZE;
  the_store.next = 0;
  return 0;
}

static int stringstore_checksize(void)
{
  char **newstr;

  if (the_store.next == the_store.size)
  {
    newstr = realloc(the_store.strings, (the_store.size + STRINGSTORE_BLOCKSIZE) * sizeof(char *));

    if (!newstr)
    {
      fprintf(stderr, "realloc stringstore failed.\n");
      return -1;
    }
    the_store.strings = newstr;
    the_store.size += STRINGSTORE_BLOCKSIZE;
  }
  return 0;
}

int stringstore_find(const char *src, int len)
{
  return hashtable_has(src, len);
}

int stringstore_add(const char *src, int len)
{
  int ret;

  ret = hashtable_has(src, len);

  if (ret == -1)
  {
    if (!stringstore_checksize())
    {
      char *ns = calloc(len + 1, sizeof(char));

      if (ns)
      {
        strncpy(ns, src, len);
        ns[len] = '\0';
        ret = the_store.next++;
        the_store.strings[ret] = ns;
        hashtable_add(ret);
      }
      else
      {
        fprintf(stderr, "could not allocate string entry.\n");
        exit(1);
      }
    }
  }

  return ret;
}

const char *stringstore_get(int entry)
{
  if (entry >= 0 && entry < the_store.next)
    return (const char *)the_store.strings[entry];
  return NULL;
}

void stringstore_free(void)
{
  int i;
  for (i = 0; i < BUCKETS; i++)
  {
    struct hashlist *entry = table.entries[i];

    while (entry)
    {
      struct hashlist *n = entry->next;
      free(entry);
      entry = n;
    }
  }

  if (the_store.strings)
  {
    for (i = 0; i < the_store.next; i++)
    {
      free(the_store.strings[i]);
    }
    free(the_store.strings);
    the_store.strings = NULL;
    the_store.size = 0;
    the_store.next = 0;
  }
}
