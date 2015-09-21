// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-17-0-1 %t

// Some allowed defines
#define LEGAL_DEFINE
#define DATE "today"
#define FILE myfile.cpp
#define LINE 123
#define STDC_HOSTED 1
#define TIME 0
#define STDC 1
#define ERRNO 99

#undef LEGAL_DEFINE
#undef DATE
#undef FILE
#undef LINE
#undef STDC_HOSTED
#undef TIME
#undef STDC
#undef ERRNO
#undef ASSERT

// The few cases where a macro with two leading underscore can be user specified
#define __STDC_FORMAT_MACROS
#include <stdint.h>
#define __STDC_LIMIT_MACROS
#include <inttypes.h>

// Disallowed usages
#define __cplusplus                         // CHECK-MESSAGES: :[[@LINE]]:9: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#define __DATE__                            // CHECK-MESSAGES: :[[@LINE]]:9: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#define __FILE__                            // CHECK-MESSAGES: :[[@LINE]]:9: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#define __LINE__                            // CHECK-MESSAGES: :[[@LINE]]:9: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#define __STDC_HOSTED__                     // CHECK-MESSAGES: :[[@LINE]]:9: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#define __TIME__                            // CHECK-MESSAGES: :[[@LINE]]:9: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#define __STDC__                            // CHECK-MESSAGES: :[[@LINE]]:9: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#define __STDC_MB_MIGHT_NEQ_WC__            // CHECK-MESSAGES: :[[@LINE]]:9: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#define __STDC_VERSION__                    // CHECK-MESSAGES: :[[@LINE]]:9: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#define __STDC_ISO_10646__                  // CHECK-MESSAGES: :[[@LINE]]:9: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#define __STDCPP_STRICT_POINTER_SAFETY__    // CHECK-MESSAGES: :[[@LINE]]:9: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#define __STDCPP_THREADS__                  // CHECK-MESSAGES: :[[@LINE]]:9: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#define errno                               // CHECK-MESSAGES: :[[@LINE]]:9: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#define assert                              // CHECK-MESSAGES: :[[@LINE]]:9: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#define _ILLEGAL_NAME_WITH_UNDERSCORE_FIRST // CHECK-MESSAGES: :[[@LINE]]:9: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]

#undef __cplusplus                         // CHECK-MESSAGES: :[[@LINE]]:8: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#undef __DATE__                            // CHECK-MESSAGES: :[[@LINE]]:8: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#undef __FILE__                            // CHECK-MESSAGES: :[[@LINE]]:8: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#undef __LINE__                            // CHECK-MESSAGES: :[[@LINE]]:8: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#undef __STDC_HOSTED__                     // CHECK-MESSAGES: :[[@LINE]]:8: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#undef __TIME__                            // CHECK-MESSAGES: :[[@LINE]]:8: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#undef __STDC__                            // CHECK-MESSAGES: :[[@LINE]]:8: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#undef __STDC_MB_MIGHT_NEQ_WC__            // CHECK-MESSAGES: :[[@LINE]]:8: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#undef __STDC_VERSION__                    // CHECK-MESSAGES: :[[@LINE]]:8: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#undef __STDC_ISO_10646__                  // CHECK-MESSAGES: :[[@LINE]]:8: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#undef __STDCPP_STRICT_POINTER_SAFETY__    // CHECK-MESSAGES: :[[@LINE]]:8: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#undef __STDCPP_THREADS__                  // CHECK-MESSAGES: :[[@LINE]]:8: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#undef errno                               // CHECK-MESSAGES: :[[@LINE]]:8: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#undef assert                              // CHECK-MESSAGES: :[[@LINE]]:8: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#undef _ILLEGAL_NAME_WITH_UNDERSCORE_FIRST // CHECK-MESSAGES: :[[@LINE]]:8: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]

#undef define  // CHECK-MESSAGES: :[[@LINE]]:8: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
#define define // CHECK-MESSAGES: :[[@LINE]]:9: warning: Reserved identifiers, macros and functions in the standard library shall not be defined, redefined or undefined. [misra-cpp2008-17-0-1]
