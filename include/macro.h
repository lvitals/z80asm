#ifndef _MACRO_H_
#define _MACRO_H_

#include "label.h"

/* macro stuff */
struct macro_arg
{
  struct macro_arg *next;
  unsigned pos;
  unsigned which;
};

struct macro_line
{
  struct macro_line *next;
  int line;
  struct macro_arg *args;
};

struct macro
{
  struct macro *next;
  int name;
  unsigned numargs;
  int *args;
  struct macro_line *lines;
  struct label *labels;
};

#endif
