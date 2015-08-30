// RUN: %python %S/../check_clang_tidy.py %s misra-c2012-17.1 %t

#include <stdint.h>
#include <stdarg.h> // CHECK-MESSAGES: [[@LINE]]:1: warning: The features of <stdarg.h> shall not be used [misra-c2012-17.1]

void f(uint8_t count, ...) {
  va_list l1, l2;          // CHECK-MESSAGES: [[@LINE]]:3: warning: The features of <stdarg.h> shall not be used [misra-c2012-17.1]
  va_start(l1, count);     // CHECK-MESSAGES: [[@LINE]]:3: warning: The features of <stdarg.h> shall not be used [misra-c2012-17.1]
  va_copy(l2, l1);         // CHECK-MESSAGES: [[@LINE]]:3: warning: The features of <stdarg.h> shall not be used [misra-c2012-17.1]
  int v = va_arg(l1, int); // CHECK-MESSAGES: [[@LINE]]:11: warning: The features of <stdarg.h> shall not be used [misra-c2012-17.1]
  (void)v;
  va_end(l1); // CHECK-MESSAGES: [[@LINE]]:3: warning: The features of <stdarg.h> shall not be used [misra-c2012-17.1]
}
