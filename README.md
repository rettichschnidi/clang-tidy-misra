About [![Build Status](https://travis-ci.org/rettichschnidi/clang-tidy-misra.svg?branch=master)](https://travis-ci.org/rettichschnidi/clang-tidy-misra)
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2Frettichschnidi%2Fclang-tidy-misra.svg?type=shield)](https://app.fossa.io/projects/git%2Bgithub.com%2Frettichschnidi%2Fclang-tidy-misra?ref=badge_shield)
=====

clang-tidy-misra is a collection of MISRA compliance checkers for clang-tidy.

Progress
========
This project is in an early stage and has not yet been tested extensively!

If and how each rule can be checked:
* [MISRA C++:2008](doc/cpp2008.md)
* [MISRA C:2012](doc/c2012.md)

Explanation for the "Supported by" column:
* TBD: "To Be Determined" - Rule has not yet been looked at at all
* unchecked: Rule can not (yet) be checked at all
* unchecked (document): Unchecked and likely uncheckable by a compiler
* -...: Enforceable by enabling this option when invoking the compiler
* misra-...: Checker developed by us is able to check this rule
* ...: Checkable by the vanilla clang-tidy checker

Work plan
=========
Work to do, not necessarily in the listed order:

- Implement/Cover as many rules as possible
- Integrate all checkers into a unified web front end that supports the user
with the creation of all the necessary documentation (compliance matrix,
deviations, sign-offs, etc.) to achieve MISRA compliance

Installation
============
No documentation so far. `.travis.yml` and `travis/build.sh` may be useful.

Bugs
====
When reporting a bug, please include a code snippet which triggers the flaw.

Contribute a checker
====================
* Check the `test-wishlist` folder for already existing test code
* Move/Add a file, e.g. `10-3-2.cpp` with test cases to the `test` folder
* Make sure existing can not yet check this rule
 * `clang-tidy -checks=* 10-3-2.cpp`
 * `clang++ -fsyntax-only -Weverything 10-3-2.cpp`
* Add support for this rule
 * Implement checker logic if needed - [Dumping the AST](http://clang.llvm.org/docs/IntroductionToTheClangAST.html#examining-the-ast)
of your test code may help you
 * If vanilla Clang/clang-tidy does the trick, adapt the test
* Call `make check-tidy-misra` in the build directory to run the tests
* Highly recommended: Let the new checker run on your embedded project(s) to
make sure it works as intended
* Commit and create a pull request

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

Usage
=====
Enable the rules `misra-*` when using [clang-tidy](http://clang.llvm.org/extra/clang-tidy.html).


## License
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2Frettichschnidi%2Fclang-tidy-misra.svg?type=large)](https://app.fossa.io/projects/git%2Bgithub.com%2Frettichschnidi%2Fclang-tidy-misra?ref=badge_large)