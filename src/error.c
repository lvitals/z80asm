#include <stdarg.h>
#include <stdlib.h>
#include "error.h"

#include "files.h"
#include "stack.h"
#include "stringstore.h"

/* print an error message, including current line and file */
void printerr(int error, const char *fmt, ...)
{
  va_list l;
  va_start(l, fmt);
  if ((sp < 0) || (stack[sp].name == 0))
  {
    fprintf(stderr, "internal assembler error, sp == %i\n", sp);
    vfprintf(stderr, fmt, l);

    exit(2);
  }
  fprintf(stderr, "%s%s:%d: %s: ", stack[sp].dir ? stringstore_get(stack[sp].dir->name) : "",
          stringstore_get(stack[sp].name), stack[sp].line, error ? "error" : "warning");
  vfprintf(stderr, fmt, l);
  va_end(l);
  if (error)
    errors++;
}
