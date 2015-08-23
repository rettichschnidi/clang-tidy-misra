// RUN: "%clang"-tidy -checks=misra-c2012-17.1 %s -- | FileCheck %s
#include <stdint.h>
#include <stdarg.h> // CHECK: 17.1.c:[[@LINE]]:1: error: The features of <stdarg.h> shall not be used [misra-c2012-17.1]

void f(uint8_t count, ...) {
  va_list l1, l2;          // CHECK: 17.1.c:[[@LINE]]:3: error: The features of <stdarg.h> shall not be used [misra-c2012-17.1]
  va_start(l1, count);     // CHECK: 17.1.c:[[@LINE]]:3: error: The features of <stdarg.h> shall not be used [misra-c2012-17.1]
  va_copy(l2, l1);         // CHECK: 17.1.c:[[@LINE]]:3: error: The features of <stdarg.h> shall not be used [misra-c2012-17.1]
  int v = va_arg(l1, int); // CHECK: 17.1.c:[[@LINE]]:11: error: The features of <stdarg.h> shall not be used [misra-c2012-17.1]
  (void)v;
  va_end(l1); // CHECK: 17.1.c:[[@LINE]]:3: error:  The features of <stdarg.h> shall not be used [misra-c2012-17.1]
}
