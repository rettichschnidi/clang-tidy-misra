// RUN: %python %S/../check_clang_tidy.py %s misra-c2012-6.2 %t

struct S {
  signed int a : 1;   // CHECK-MESSAGES: [[@LINE]]:3: warning: Single-bit named bit fields shall not be of a signed type [misra-c2012-6.2]
  signed int : 1;     // Unnamed - Compliant
  unsigned int b : 1; // Unsigned - Compliant
};
