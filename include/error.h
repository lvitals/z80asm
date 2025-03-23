#ifndef _ERROR_H_
#define _ERROR_H_

extern int errors;
extern int verbose;

/* print an error message, including current line and file */
void printerr (int error, const char *fmt, ...);

#endif
