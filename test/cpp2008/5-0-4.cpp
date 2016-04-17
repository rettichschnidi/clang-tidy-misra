// RUN: %clang -fsyntax-only -Wsign-conversion -Xclang -verify %s

signed int s = 0;
unsigned int u = 0U;

signed int s1 = s;
unsigned int u1 = u;

signed int s2 = u;   // expected-warning {{implicit conversion changes signedness: 'unsigned int' to 'int'}}
unsigned int u2 = s; // expected-warning {{implicit conversion changes signedness: 'int' to 'unsigned int'}}

signed int s3 = static_cast<signed int>(u);
signed int s4 = static_cast<unsigned int>(u); // expected-warning {{implicit conversion changes signedness: 'unsigned int' to 'int'}}

unsigned int u3 = static_cast<unsigned int>(s);
unsigned int u4 = static_cast<signed int>(s); // expected-warning {{implicit conversion changes signedness: 'int' to 'unsigned int'}}

unsigned int funMixedIntegerWidths(unsigned int a, unsigned short b) {
  return a + b;
}

enum UnsignedEnum {
  MY_UNSIGNED_ENUM_ENTRY_1,
  MY_UNSIGNED_ENUM_ENTRY_2,
};

void funUnsignedEnum(UnsignedEnum se) {
  bool aa = se == MY_UNSIGNED_ENUM_ENTRY_1;
  bool bb = se != MY_UNSIGNED_ENUM_ENTRY_1;
  bool ff = se != MY_UNSIGNED_ENUM_ENTRY_1;
}

enum SignedEnum {
  MY_SIGNED_ENUM_ENTRY_1 = -1,
  MY_SIGNED_ENUM_ENTRY_2,
};

void funSigned(SignedEnum ue) {
  bool aa = ue == MY_SIGNED_ENUM_ENTRY_1;
  bool bb = ue != MY_SIGNED_ENUM_ENTRY_1;
  bool ff = ue != MY_SIGNED_ENUM_ENTRY_1;
}

bool funMixed(SignedEnum se, UnsignedEnum ue) {
  return (int)se == (int)ue;
}
