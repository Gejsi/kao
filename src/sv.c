#include "sv.h"
#include <string.h>

StringView StringView_new(const char *value, unsigned long length) {
  StringView sv;
  sv.value = value;
  sv.length = length;
  return sv;
}

StringView StringView_from_cstr(const char *cstr) {
  return StringView_new(cstr, strlen(cstr));
}

StringView StringView_append(StringView *a, StringView *b) {
  char new_value[a->length + b->length + 1]; // +1 for null terminator

  memcpy(new_value, a->value, a->length);
  memcpy(new_value + a->length, b->value, b->length);
  new_value[a->length + b->length] = '\0';

  return StringView_new(new_value, a->length + b->length);
}

bool StringView_equals(StringView *a, StringView *b) {
  if (a->length != b->length) {
    return false;
  } else {
    return memcmp(a->value, b->value, a->length) == 0;
  }
}
