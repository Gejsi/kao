#ifndef HS_H
#define HS_H

typedef struct {
  char *value;
  unsigned long length;
} String;

void String_init(String *self);
void String_free(String *self);
int String_push(String *self, const char *str);

#endif // HS_H
