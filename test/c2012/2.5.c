// RUN: %clang -std=c99 -Wunused-macros -fsyntax-only -ferror-limit=0 -Xclang -verify %s

#define ONE 1
#define TWO 2 // expected-warning {{macro is not used}}

unsigned int function(void) {
  return ONE;
}
