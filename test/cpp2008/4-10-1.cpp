// RUN: %clang -fsyntax-only -Wnull-conversion -ferror-limit=0 -Xclang -verify %s

#include <cstddef>

void f1(int i);
void f2(int *p);

class T {
public:
  void f(int p);
};

template <typename T>
void tf(T t);

class C {
  void f();
};

void test_function() {
  f1(0);
  f1(NULL); // expected-warning {{implicit conversion of NULL constant to 'int'}}

  f2(0);
  f2(NULL);

  T t;
  t.f(0);
  t.f(NULL); // expected-warning {{implicit conversion of NULL constant to 'int'}}

  tf<int>(0);
  tf<int>(NULL); // expected-warning {{implicit conversion of NULL constant to 'int'}}

  size_t c = 0;
  bool d = c == 0;
  int a = NULL;       // expected-warning {{implicit conversion of NULL constant to 'int'}}
  bool b = a == NULL; // expected-warning {{comparison between NULL and non-pointer}}
}
