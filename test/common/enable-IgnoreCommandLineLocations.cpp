// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-17-0-1 %t -config='{CheckOptions: [{key: misra.IgnoreCommandLineLocations, value: 1}]}' -- -D__MY_DANGEROUS_MACRO
// Do not generate an error for -D__MY_DANGEROUS_MACRO

#define __cplusplus // CHECK-MESSAGES: :[[@LINE]]:9: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
