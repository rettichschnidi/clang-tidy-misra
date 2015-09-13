// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-9-5-1 %t

union MyNastyIllegalUnion { // CHECK-MESSAGES: :[[@LINE]]:7: warning: Unions shall not be used. [misra-cpp2008-9-5-1]
  int i;
  float f;
};
