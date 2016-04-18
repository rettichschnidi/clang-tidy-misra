// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-17-0-1 %t -config='{CheckOptions: [{key: misra-cpp2008-17-0-1.IgnoreCommandLineLocations, value: 0}]}' -- -D__MY_DANGEROUS_MACRO

// CHECK-MESSAGES: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
