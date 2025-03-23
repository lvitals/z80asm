#ifndef _LABEL_H_
#define _LABEL_H_

#include "reference.h"

/* labels (will be malloced) */
struct label
{
  struct label *next, *prev;	/* linked list */
  int value;			/* value */
  int valid;			/* if it is valid, or not yet computed */
  int busy;			/* if it is currently being computed */
  struct reference *ref;	/* mallocced memory to value for computation */
  int name;			/* space with name in it */
};


#endif
