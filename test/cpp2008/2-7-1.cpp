// RUN: %clang++ -std=c++03 -Wcomment -fsyntax-only -ferror-limit=0 -Xclang -verify %s

/* This is a comment before the important code
check_safety_critical_stuff();
/* This is a comment after the important code*/ // expected-warning {{'/*' within block comment}}
