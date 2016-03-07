// RUN: %clang -std=c99  -Wunused-label -fsyntax-only -ferror-limit=0 -Xclang -verify %s

#include <stdint.h>

int use_int16(int16_t x);

void function(void) {
  int16_t x = 6;
unused_label: // expected-warning {{unused label 'unused_label'}}
  use_int16(x);
}
