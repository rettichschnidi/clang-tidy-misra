#define MakeSquare(x) ((x) * (x))
struct MakeSquare { // Non-Compliant
  int a;
};

#define addOne(x) ((x) + 1)
int addOne; // Non-Compliant

#define addTwo(x) ((x) + 2)
int i = addTwo(1); // Compliant

#define this_is_a_too_long_identifier_1
int this_is_a_too_long_identifier_2; // Non-Compliant
