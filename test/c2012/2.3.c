// RUN: %clang -std=c99 -Wunused-local-typedef -fsyntax-only -ferror-limit=0 -Xclang -verify %s

unsigned int function(void) {
  typedef unsigned int UINT; // expected-warning {{unused typedef 'UINT'}}
  return 1;
}
