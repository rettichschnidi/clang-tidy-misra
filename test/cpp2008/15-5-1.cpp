// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-15-5-1 %t

#include <stdexcept>

class A {
public:
  ~A() {
    throw std::runtime_error(""); // CHECK-MESSAGES: :[[@LINE]]:5: warning: A class destructor shall not exit with an exception. [misra-cpp2008-15-5-1]
  }
};

class B {
public:
  ~B() {
    throw std::runtime_error(""); // CHECK-MESSAGES: :[[@LINE]]:5: warning: A class destructor shall not exit with an exception. [misra-cpp2008-15-5-1]
  }
};

class C {
public:
  ~C();
};

C::~C() {
  try {
    throw std::runtime_error("");
  } catch (const std::exception &ex) { // Compliant
  }
}

class D {
  ~D() noexcept;
};

D::~D() noexcept {
  throw std::runtime_error(""); // CHECK-MESSAGES: :[[@LINE]]:3: warning: A class destructor shall not exit with an exception. [misra-cpp2008-15-5-1]
}

class MoreComplicated {
public:
  ~MoreComplicated() {
    if (test()) {
      fun();
    }
    if (test()) {
      if (test()) {
        fun();
        throw std::domain_error(""); // CHECK-MESSAGES: :[[@LINE]]:9: warning: A class destructor shall not exit with an exception. [misra-cpp2008-15-5-1]
      }
    }
  }

  void fun() {
    for (int i = 0; i < 10; ++i) {
    }
  }

  bool test() {
    return true;
  }
};

void fun() {
  A a;
}
