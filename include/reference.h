#ifndef _REFERENCE_H_
#define _REFERENCE_H_

/* types of reference */
enum reftype
{
  TYPE_BSR,			/* bit value (0-7) for bit, set and res */
  TYPE_DS,			/* ds reference (byte count and value) */
  TYPE_RST,			/* rst reference: val & 0x38 == val */
  TYPE_ABSW,			/* absolute word (2 bytes) */
  TYPE_ABSB,			/* absolute byte */
  TYPE_RELB,			/* relative byte */
  TYPE_LABEL			/* equ expression */
};

/* these structs will be malloced for each reference */
struct reference
{
  struct reference *next, *prev;
  enum reftype type;		/* type of reference */
  long oseekpos;		/* position in outfile for data */
  long lseekpos;		/* position in listfile for data */
  char delimiter;		/* delimiter for parser */
  int addr, line;		/* address and line of reference */
  int baseaddr;			/* address at start of line of reference */
  int comma;			/* comma when reference was set */
  int count;			/* only for ds: number of items */
  int infile;			/* index in infile[], current infile */
  int done;			/* if this reference has been computed */
  int computed_value;		/* value (only valid if done = true) */
  int level;			/* maximum stack level of labels to use */
  struct includedir *dir;	/* dirname of file (for error reporting) */
  int file;			/* filename (for error reporting) */
  char input[1];		/* variable size buffer containing formula */
};

#endif
