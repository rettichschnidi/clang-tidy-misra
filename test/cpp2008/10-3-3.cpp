// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-10-3-3 %t

class BasePure {
public:
  virtual void badMethod() = 0;
  virtual void goodMethod() = 0;
};

class DerivedNonPure : public BasePure {
public:
  virtual void badMethod();
  virtual void goodMethod() = 0;
};

class DerivedPureAgain : public DerivedNonPure {
public:
  virtual void badMethod() = 0;  // CHECK-MESSAGES: :[[@LINE]]:16: warning: A virtual function shall only be overridden by a pure virtual function if it is itself declared as pure virtual. [misra-cpp2008-10-3-3]
  virtual void goodMethod() = 0; // Compliant - Was also pure in class DerivedNonPure
};
