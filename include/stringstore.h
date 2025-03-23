#ifndef _STRINGSTORE_H_
#define _STRINGSTORE_H_

extern int stringstore_init(void);
extern int stringstore_add(const char *src, int len);
extern const char *stringstore_get(int entry);
extern int stringstore_find(const char *src, int len);
extern void stringstore_free(void);

#endif
