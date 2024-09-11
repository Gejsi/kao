#include "hs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void String_init(String *self) {
  self->value = NULL;
  self->length = 0;
}

void String_free(String *self) {
  if (self->value != NULL) {
    free(self->value);
  }
  String_init(self);
}

bool String_push(String *self, const char *str) {
  if (!str) {
    return false;
  }

  size_t str_len = strlen(str);
  char *new_data = realloc(self->value, self->length + str_len + 1);

  if (new_data) {
    memcpy(new_data + self->length, str, str_len + 1);
    self->value = new_data;
    self->length += str_len;
    return true;
  } else {
    perror("Failed to allocate more memory for the string");
    return false;
  }
}
