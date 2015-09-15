// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-10-3-2 %t

class A {
public:
  virtual void badMethod();
  virtual void goodMethod();
  virtual ~A();
};

class B1 : public A {
public:
  void badMethod();          // CHECK-MESSAGES: :[[@LINE]]:8: warning: Each overriding virtual function shall be declared with the virtual keyword. [misra-cpp2008-10-3-2]
  virtual void goodMethod(); // Compliant - Explicitly declared virtual
  virtual ~B1();
};

class B2 : public A {
public:
  void badMethod();          // CHECK-MESSAGES: :[[@LINE]]:8: warning: Each overriding virtual function shall be declared with the virtual keyword. [misra-cpp2008-10-3-2]
  virtual void goodMethod(); // Compliant - Explicitly declared virtual
  ~B2();                     // CHECK-MESSAGES: :[[@LINE]]:3: warning: Each overriding virtual function shall be declared with the virtual keyword. [misra-cpp2008-10-3-2]
};

B2::~B2() {}             // No virtual specifier required here
void B2::goodMethod() {} // No virtual specifier required here

class B3 : public A {
  // ~B3(); // Compliant - implicit destructor is OK, even when virtual
};
