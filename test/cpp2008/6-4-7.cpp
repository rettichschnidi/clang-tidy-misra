// RUN: %clang++ -Wswitch-bool -fsyntax-only -ferror-limit=0 -Xclang -verify %s

void violatingSwitch(int x) {
  switch (x == 1) { // expected-warning {{switch condition has boolean value}}
  }
  switch (x > 1) { // expected-warning {{switch condition has boolean value}}
  }
  switch (x != 1) { // expected-warning {{switch condition has boolean value}}
  }
  switch (x) { // Compliant
  }
}
