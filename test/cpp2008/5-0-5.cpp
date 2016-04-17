// RUN: %clang -fsyntax-only -Wliteral-conversion -Xclang -verify %s

int iFromF = 3.5F; // expected-warning {{implicit conversion from 'float' to 'int' changes value from 3.5 to 3}}
int iFromD = 3.5;  // expected-warning {{implicit conversion from 'double' to 'int' changes value from 3.5 to 3}}
