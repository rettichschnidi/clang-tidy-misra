// RUN: "%clang"-tidy -checks='-*,misra-c2012-17.1' %s -- | FileCheck %s

#include <stdint.h>
// CHECK: 17.1.c:[[@LINE+1]]:1: error: The features of <stdarg.h> shall not be used [misra-c2012-17.1]
#include <stdarg.h>

void f(uint8_t count, ...) {
  // CHECK: 17.1.c:[[@LINE+1]]:3: error: The features of <stdarg.h> shall not be used [misra-c2012-17.1]
  va_list l1, l2;
  // CHECK: 17.1.c:[[@LINE+1]]:3: error: The features of <stdarg.h> shall not be used [misra-c2012-17.1]
  va_start(l1, count);
  // CHECK: 17.1.c:[[@LINE+1]]:3: error: The features of <stdarg.h> shall not be used [misra-c2012-17.1]
  va_copy(l2, l1);
  // CHECK: 17.1.c:[[@LINE+1]]:11: error: The features of <stdarg.h> shall not be used [misra-c2012-17.1]
  int v = va_arg(l1, int);
  (void)v;
  // CHECK: 17.1.c:[[@LINE+1]]:3: error:  The features of <stdarg.h> shall not be used [misra-c2012-17.1]
  va_end(l1);
}
