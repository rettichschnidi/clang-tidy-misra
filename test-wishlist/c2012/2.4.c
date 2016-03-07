// RUN: %python %S/../check_clang_tidy.py %s misra-c2012-2.4 %t

void function() {
  enum Color { RED,
               GREEN }; // CHECK-MESSAGES: [[@LINE]]:1: warning: A project should not contain unused tag declarations [misra-c2012-2.4]
}

enum FRUIT { APPLE,
             BANANA };

enum FRUIT functionBanana() {
  return BANANA;
}
