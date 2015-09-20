// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-16-3-1 %t

// Some allowed defines
#define MAKE_STRING1(s) #s
#define MAKE_STRING2(s) "hello " #s
#define COMBINE(s1, s2) s1##s2
#define MAKE_NOTHING(x)

// Disallowed usages
#define TRIPPLE_CONCAT(s) s##s##s              // CHECK-MESSAGES: :[[@LINE]]:31: warning: There shall be at most one occurrence of the # or ## operators in a single macro definition. [misra-cpp2008-16-3-1]
#define DOUBLE_STRINGIFY(s1, s2) #s1 #s2       // CHECK-MESSAGES: :[[@LINE]]:38: warning: There shall be at most one occurrence of the # or ## operators in a single macro definition. [misra-cpp2008-16-3-1]
#define STRINGIFY_CONCAT1(s1, s2) #s1##s2      // CHECK-MESSAGES: :[[@LINE]]:38: warning: There shall be at most one occurrence of the # or ## operators in a single macro definition. [misra-cpp2008-16-3-1]
#define STRINGIFY_CONCAT2(s1, s2) s1##s2 #s1   // CHECK-MESSAGES: :[[@LINE]]:42: warning: There shall be at most one occurrence of the # or ## operators in a single macro definition. [misra-cpp2008-16-3-1]
#define STRINGIFY_MULTILINE(s1, s2) s1##s2 #s1 // CHECK-MESSAGES: :[[@LINE]]:44: warning: There shall be at most one occurrence of the # or ## operators in a single macro definition. [misra-cpp2008-16-3-1]
