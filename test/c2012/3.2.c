// RUN: %clang -std=c99 -Wcomment -fsyntax-only -ferror-limit=0 -Xclang -verify %s

int makeAbs(int i) {

  // expected-warning@+1 {{multi-line // comment}}
  if (i < 0) { // Invert numbers only if needed \
    i *= -1;
  }
  return i;
}
