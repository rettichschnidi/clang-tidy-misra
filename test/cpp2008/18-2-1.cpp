// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-18-2-1 %t

#include <cstddef>

struct A {
  int one;
};

int i = offsetof(A, one); // CHECK-MESSAGES: :[[@LINE]]:9: warning: The macro offsetof shall not be used. [misra-cpp2008-18-2-1]
