//===--- 2-13-3.h - clang-tidy-misra ----------------------------*- C++ -*-===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef CLANG_TIDY_MISRA_CPP_2008_RULE_2_13_3_H
#define CLANG_TIDY_MISRA_CPP_2008_RULE_2_13_3_H

#include "ClangTidyMisraCheck.h"

namespace clang {
namespace tidy {
namespace misra {
namespace cpp2008 {

class Rule_2_13_3 : public ClangTidyMisraCheck {
public:
  Rule_2_13_3(StringRef Name, ClangTidyContext *Context);
  virtual void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  virtual void
  checkImpl(const ast_matchers::MatchFinder::MatchResult &Result) override;

private:
  bool isUnsignedIntegerLiteral(const IntegerLiteral *il);

  /// \brief Make sure the suffix 'U' exists.
  /// \param il Unsigned integer literal.
  void dealWithUnsignedInteger(const IntegerLiteral *intLiteral);
};

} // cpp2008
} // namespace misra
} // namespace tidy
} // namespace clang

#endif // CLANG_TIDY_MISRA_CPP_2008_RULE_2_13_3_H
