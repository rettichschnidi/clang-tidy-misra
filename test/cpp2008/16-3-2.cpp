// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-16-3-2 %t

// Disallowed usages
#define CONCAT(s) HELLO##s                 // CHECK-MESSAGES: :[[@LINE]]:24: warning: The # and ## operators should not be used. [misra-cpp2008-16-3-2]
#define STRINGIFY(s) #s                    // CHECK-MESSAGES: :[[@LINE]]:22: warning: The # and ## operators should not be used. [misra-cpp2008-16-3-2]
#define STRINGIFY_MULTILINE(s) "HELLO " #s // CHECK-MESSAGES: :[[@LINE]]:41: warning: The # and ## operators should not be used. [misra-cpp2008-16-3-2]
