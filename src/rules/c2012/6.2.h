//===--- 6.2.h - clang-tidy-misra -------------------------------*- C++ -*-===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef CLANG_TIDY_MISRA_C_2012_RULE_6_2_H
#define CLANG_TIDY_MISRA_C_2012_RULE_6_2_H

#include "ClangTidyMisraCheck.h"

namespace clang {
namespace tidy {
namespace misra {
namespace c2012 {

class Rule_6_2 : public ClangTidyMisraCheck {
public:
  Rule_6_2(StringRef Name, ClangTidyContext *Context);
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void checkImpl(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

} // c2012
} // namespace misra
} // namespace tidy
} // namespace clang

#endif // CLANG_TIDY_MISRA_C_2012_RULE_6_2_H
