//===--- 10-3-3.cpp - clang-tidy-misra ------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "10-3-3.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/CompilerInstance.h"

namespace clang {
namespace tidy {
namespace misra {
namespace cpp2008 {

using namespace clang::ast_matchers;

Rule_10_3_3::Rule_10_3_3(llvm::StringRef Name, ClangTidyContext *Context)
    : ClangTidyMisraCheck(Name, Context) {}

void Rule_10_3_3::registerMatchers(ast_matchers::MatchFinder *Finder) {
  Finder->addMatcher(cxxMethodDecl(isPure()).bind("PureMethod"), this);
}

void Rule_10_3_3::checkImpl(
    const ast_matchers::MatchFinder::MatchResult &Result) {
  if (const auto *methodDecl =
          Result.Nodes.getNodeAs<CXXMethodDecl>("PureMethod")) {
    for (auto I = getASTContext().overridden_methods_begin(methodDecl),
              E = getASTContext().overridden_methods_end(methodDecl);
         I != E; ++I) {
      if (!(*I)->isPure()) {
        diag(methodDecl->getLocation());
        break;
      }
    }
  }
}

} // namespace cpp2008
} // namespace misra
} // namespace tidy
} // namespace clang
