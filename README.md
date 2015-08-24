About
=====

clang-tidy-misra is a collection of MISRA compliance checkers for clang-tidy.

Progress
========
This project is in an early stage and has not yet been tested extensively!

Work plan
=========
Work to do, not necessarily in the listed order:

- Implement/Cover as many rules as possible
- Integrate all checkers into a unified web front end that supports the user
with the creation of all the necessary documentation (compliance matrix,
deviations, sign-offs, etc.) to achieve MISRA compliance

Installation
============
TBD

Bugs
====
When reporting a bug, please include a code snippet which triggers the flaw.

Contributions
=============
1. Make sure the rule is not yet covered
2. Check the `test-wishlist` folder for already existing test code
3. Move/Add a file with the test cases to the `test` folder
4. Implement checker logic - [Dumping the AST](http://clang.llvm.org/docs/IntroductionToTheClangAST.html#examining-the-ast)
of your test code may help you
5. Call `make check-tidy-misra` in the build directory to run the tests
6. Highly recommended, but optional: Let the new checker run on your embedded
project(s) to make sure it works as intended
7. Commit and create a pull request

In case you figure that you can not come up with some usable checker logic,
instead of hiding away or deleting your test code, please move it from `test` to
`test-wishlist` where it can be picked up by someone else.

Coding Style
============
This project follows (tries to...) the [LLVM Coding Standard](http://llvm.org/docs/CodingStandards.html).
At the very least the code has to be formatted using clang-format and the LLVM
coding style.

For testing code feel free to lift the restrictions as necessary. For example,
by using the `.clang-format` file in the test directory.

Running Tests
=============
`make check-tidy-misra`

Building Documentation
======================
TBD

Usage
=====
Enable the rules `misra-*` when using [clang-tidy](http://clang.llvm.org/extra/clang-tidy.html).
