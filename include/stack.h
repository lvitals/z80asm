#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>

#ifndef MAX_INCLUDE
#define MAX_INCLUDE 200		/* stack size for include command and macros */
#endif

/* elements on the context stack */
struct stack
{
  int name;		/* filename (for errors). stringstore index */
  struct includedir *dir;	/* directory where it comes from, if any */
  FILE *file;			/* the handle */
  int line;			/* the current line number (for errors) */
  int shouldclose;		/* if this file should be closed when done */
  struct label *labels;		/* local labels for this stack level */
  /* if file is NULL, this is a macro entry */
  struct macro *macro;
  struct macro_line *macro_line;
  int *macro_args;		/* arguments given to the macro */
};

/* file (and macro) stack */
extern int sp;

extern struct stack stack[MAX_INCLUDE];	/* maximum level of includes */

#endif
