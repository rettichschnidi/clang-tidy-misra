// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-12-8-2 %t

struct MyForwardDeclaredStruct;

class B1 {
public:
  B1();
  virtual void f() = 0;
  B1 &operator=(B1 const &rhs); // CHECK-MESSAGES: :[[@LINE]]:7: warning: The copy assignment operator shall be declared protected or private in an abstract class. [misra-cpp2008-12-8-2]
};

class D1 : public B1 {
public:
  virtual void f() {}
  D1 &operator=(D1 const &rhs);

private:
  int member;
};

class B2 {
public:
  B2();
  virtual void f() = 0;

private:
  B2 &operator=(B2 const &rhs); // Compliant
};
