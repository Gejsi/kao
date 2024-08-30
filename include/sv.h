#ifndef SV_H
#define SV_H

typedef struct {
  const char *value;
  unsigned long length;
} StringView;

StringView StringView_new(const char *value, unsigned long length);
StringView StringView_from_cstr(const char *cstr);
StringView StringView_append(StringView *a, StringView *b);
bool StringView_equals(StringView *a, StringView *b);

#endif // SV_H
