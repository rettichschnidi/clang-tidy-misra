//===--- 17.1.h - clang-tidy-misra ----------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef CLANG_TIDY_MISRA_C_2012_RULE_17_1_H
#define CLANG_TIDY_MISRA_C_2012_RULE_17_1_H

#include "ClangTidyMisraCheck.h"

namespace clang {
namespace tidy {
namespace misra {
namespace c2012 {

class Rule_17_1 : public ClangTidyMisraCheck {
public:
  Rule_17_1(StringRef Name, ClangTidyContext *Context);
  void registerPPCallbacks(CompilerInstance &Compiler) override;
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

} // c2012
} // namespace misra
} // namespace tidy
} // namespace clang

#endif // CLANG_TIDY_MISRA_C_2012_RULE_17_1_H
