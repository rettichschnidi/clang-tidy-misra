// RUN: %clang -std=c99 -pedantic-errors -fsyntax-only -ferror-limit=0 -Xclang -verify %s

int i = 0b101010;  // expected-error {{binary integer literals are a GNU extension}}
