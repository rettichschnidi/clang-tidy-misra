// RUN: %clang -std=c99 -fsyntax-only -ferror-limit=0 -Xclang -verify %s
// expected-no-diagnostics

int i = 0b101010;
