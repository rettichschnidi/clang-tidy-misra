// RUN: %clang -fsyntax-only -Wno-missing-prototypes -Wconversion -Xclang -verify %s

short truncateImplicitly(int i) {
  return i; // expected-warning {{implicit conversion loses integer precision: 'int' to 'short'}}
}

short truncateExplicitly(int i) {
  return static_cast<short>(i);
}
