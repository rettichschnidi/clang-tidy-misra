// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-2-13-3 %t

unsigned int a = 1;  // CHECK-MESSAGES: :[[@LINE]]:18: warning: A "U" suffix shall be applied to all octal or hexadecimal integer literals of unsigned type. [misra-cpp2008-2-13-3]
unsigned int b = 2u; // CHECK-MESSAGES: :[[@LINE]]:18: warning: A "U" suffix shall be applied to all octal or hexadecimal integer literals of unsigned type. [misra-cpp2008-2-13-3]
unsigned int c = 3U; // Compliant

int d = 4;  // Compliant
int e = 5U; // Compliant

unsigned int fn1(unsigned int u) {
  return u + 0xFF; // CHECK-MESSAGES: :[[@LINE]]:14: warning: A "U" suffix shall be applied to all octal or hexadecimal integer literals of unsigned type. [misra-cpp2008-2-13-3]
}
unsigned int fn2(unsigned int u) {
  return u + 0xFFU; // Compliant
}
unsigned int fn3(unsigned int u) {
  return u + 255U; // Compliant
}
unsigned int trickyFunction(int) {
  return 1; // CHECK-MESSAGES: :[[@LINE]]:10: warning: A "U" suffix shall be applied to all octal or hexadecimal integer literals of unsigned type. [misra-cpp2008-2-13-3]
}
int trickyFunction(unsigned int) {
  return 2;
}
int trickyFunctionResult = trickyFunction(0x80000000); // CHECK-MESSAGES: :[[@LINE]]:43: warning: A "U" suffix shall be applied to all octal or hexadecimal integer literals of unsigned type. [misra-cpp2008-2-13-3]

unsigned int g = (unsigned int)1;
unsigned int h = static_cast<unsigned int>(1);
unsigned int i = (unsigned int)1U;
unsigned int j = static_cast<unsigned int>(1U);

unsigned char k = 1; // CHECK-MESSAGES: :[[@LINE]]:19: warning: A "U" suffix shall be applied to all octal or hexadecimal integer literals of unsigned type. [misra-cpp2008-2-13-3]
unsigned long l = 1; // CHECK-MESSAGES: :[[@LINE]]:19: warning: A "U" suffix shall be applied to all octal or hexadecimal integer literals of unsigned type. [misra-cpp2008-2-13-3]

enum UnsignedEnum {
  ENUM_UNSIGNED_ENTRY_ONE = 10, // CHECK-MESSAGES: :[[@LINE]]:29: warning: A "U" suffix shall be applied to all octal or hexadecimal integer literals of unsigned type. [misra-cpp2008-2-13-3]
  ENUM_UNSIGNED_ENTRY_TWO = 20  // CHECK-MESSAGES: :[[@LINE]]:29: warning: A "U" suffix shall be applied to all octal or hexadecimal integer literals of unsigned type. [misra-cpp2008-2-13-3]
};

enum SignedEnum {
  ENUM_SIGNED_ENTRY_ONE = 10, // Compliant
  ENUM_SIGNED_ENTRY_TWO = -20 // Compliant
};

int multiDimensionalArray[2][3][4];
static_assert(4U == sizeof(multiDimensionalArray[0U][0U]) / sizeof(multiDimensionalArray[0U][0U][0U]), "");
static_assert(4U == sizeof(multiDimensionalArray[0][0]) / sizeof(multiDimensionalArray[0][0][0]), "");
