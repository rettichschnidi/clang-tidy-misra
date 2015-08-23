//===--- ClangTidyMisraCheck.cpp - clang-tidy-misra -----------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "ClangTidyMisraCheck.h"
#include "clang/Frontend/CompilerInstance.h"
#include "RuleHeadlineTexts.h"

namespace clang {
namespace tidy {
namespace misra {

ClangTidyMisraCheck::ClangTidyMisraCheck(llvm::StringRef CheckName,
                                         ClangTidyContext *Context)
    : ClangTidyCheck(CheckName, Context), CheckName(CheckName) {}

DiagnosticBuilder ClangTidyMisraCheck::diag(SourceLocation Loc,
                                            DiagnosticIDs::Level Level) {
  return ClangTidyCheck::diag(Loc, ruleHeadlines.at(CheckName), Level);
}

bool ClangTidyMisraCheck::isC(const LangOptions &LangOpts) {
  return (LangOpts.C99 || LangOpts.C11);
}

} // namespace misra
} // namespace tidy
} // namespace clang
