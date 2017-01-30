//===--- 6-4-2.cpp - clang-tidy-misra -------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "6-4-4.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/Preprocessor.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misra {
namespace cpp2008 {

Rule_6_4_4::Rule_6_4_4(llvm::StringRef Name, ClangTidyContext *Context)
    : ClangTidyMisraCheck(Name, Context) {}

void Rule_6_4_4::registerMatchers(ast_matchers::MatchFinder *Finder) {
  Finder->addMatcher(caseStmt().bind("case"), this);
}

void Rule_6_4_4::checkImpl(
    const ast_matchers::MatchFinder::MatchResult &Result) {
  if (const CaseStmt* caseStmt = Result.Nodes.getNodeAs<CaseStmt>("case")) {
    const auto& parents = getASTContext().getParents(*caseStmt);
    if (parents.empty()) {
      diag(caseStmt->getLocStart());
      return;
    }

    for (size_t i = 0; i < parents.size(); i++) {
      if (const auto *child = parents[i].get<Stmt>()) {
        // A case may have a case for parent
        // if a case is following another case.
        if (CaseStmt::classof(child)) {
          return;
        }
        // A case must have a CompoundStmt for parent.
        if (CompoundStmt::classof(child)) {
          const auto& parents2 = getASTContext().getParents(*child);

          if (parents2.empty()) {
            diag(caseStmt->getLocStart());
            return;
          }

          for (size_t j = 0; j < parents2.size(); j++) {
            if (const auto *child2 = parents2[i].get<Stmt>()) {
            // Then the CompoundStmt must have a SwitchStmt for parent.
              if (SwitchStmt::classof(child2)) {
                return;
              }
            }
          }
        }
      }
    }

    // All other situation is wrong.
    diag(caseStmt->getLocStart());
  }
}

} // namespace cpp2008
} // namespace misra
} // namespace tidy
} // namespace clang
