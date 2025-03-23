#include <config.h>
#undef realloc

#include <sys/types.h>
#include <stdlib.h> // Include this for malloc, free, and NULL

/* Allocate an N-byte block of memory from the heap.
   If N is zero, allocate a 1-byte block.  */

void *
rpl_realloc (void *ptr, size_t n)
{
  if (!ptr) {
    if (!n) {
      return NULL;
    } else {
      return malloc (n);
    }
  }

  if (ptr && !n) {
    free(ptr); // Free the memory
    return NULL; // Return NULL after freeing
  }

  return realloc (ptr, n);
}