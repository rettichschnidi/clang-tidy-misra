// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-4-10-2 %t

#include <cstddef>

void f1(int i);
void f2(int *p);
void f3(char *p);
void f4(int, int *);

class T {
public:
  void f(int *p);
};

template <typename T>
void tf(T *);

class C {
  void f();
};

void test_function() {
  f1(0);
  f2(0); // CHECK-MESSAGES: :[[@LINE]]:6: warning: Literal zero (0) shall not be used as the null-pointer-constant. [misra-cpp2008-4-10-2]
  f3(0); // CHECK-MESSAGES: :[[@LINE]]:6: warning: Literal zero (0) shall not be used as the null-pointer-constant. [misra-cpp2008-4-10-2]
  f3(NULL);
  f3(nullptr);

  T t;
  t.f(0);     // CHECK-MESSAGES: :[[@LINE]]:7: warning: Literal zero (0) shall not be used as the null-pointer-constant. [misra-cpp2008-4-10-2]
  tf<int>(0); // CHECK-MESSAGES: :[[@LINE]]:11: warning: Literal zero (0) shall not be used as the null-pointer-constant. [misra-cpp2008-4-10-2]
  f4(0, 0);   // CHECK-MESSAGES: :[[@LINE]]:9: warning: Literal zero (0) shall not be used as the null-pointer-constant. [misra-cpp2008-4-10-2]

  f2(nullptr);
  f4(0, nullptr);

  int *a = 0;      // CHECK-MESSAGES: :[[@LINE]]:12: warning: Literal zero (0) shall not be used as the null-pointer-constant. [misra-cpp2008-4-10-2]
  bool b = a == 0; // CHECK-MESSAGES: :[[@LINE]]:17: warning: Literal zero (0) shall not be used as the null-pointer-constant. [misra-cpp2008-4-10-2]
  int *c = NULL;
  bool d = c == NULL;
  int *e = nullptr;
  bool f = e == nullptr;

  int (C::*fptrNull)() = NULL;
  int (C::*fptrNullptr)() = nullptr;
  int C::*fptr0 = 0; // CHECK-MESSAGES: :[[@LINE]]:19: warning: Literal zero (0) shall not be used as the null-pointer-constant. [misra-cpp2008-4-10-2]
}
