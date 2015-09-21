// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-17-0-5 %t

#include <setjmp.h>

jmp_buf buf;

void setup() {
  setjmp(buf); // CHECK-MESSAGES: :[[@LINE]]:3: warning: The setjmp macro and the longjmp function shall not be used. [misra-cpp2008-17-0-5]
}

void jump() {
  longjmp(buf, 1); // CHECK-MESSAGES: :[[@LINE]]:3: warning: The setjmp macro and the longjmp function shall not be used. [misra-cpp2008-17-0-5]
}
