// RUN: %clang -fsyntax-only -Wunsequenced -Xclang -verify %s

void incrementOperator(int i) {
  int b[] = {10, 20, 30};
  int x = b[i] + i++; // expected-warning {{unsequenced modification and access to 'i'}}

  i++;
  x = b[i] + i; // Compliant
}

int f(int i, int j);
void functionArguments(int i) {
  int x = f(i++, i); // expected-warning {{unsequenced modification and access to 'i'}}

  x = f(i + 1, i); // Compliant
  i++;
}

struct S {
  void method(S *);
};

void callByPointer(S pointer1[], S pointer2[]) {
  pointer1->method(pointer1++); // expected-warning {{unsequenced modification and access to 'pointer1'}}
  pointer1->method(pointer2++); // Compliant
}

void nestedAssignements(int &argToModify) {
  argToModify = argToModify++; // expected-warning {{multiple unsequenced modifications to 'argToModify'}}
}
