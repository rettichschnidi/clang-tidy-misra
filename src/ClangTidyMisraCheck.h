//===--- ClangTidyMisraCheck.h - clang-tidy-misra ---------------*- C++ -*-===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef CLANG_TIDY_MISRA_CHECK_H
#define CLANG_TIDY_MISRA_CHECK_H

#include "../../ClangTidy.h"
#include "llvm/ADT/StringRef.h"
#include <string>

namespace clang {
namespace tidy {
namespace misra {

class ClangTidyMisraCheck : public ClangTidyCheck {
public:
  ClangTidyMisraCheck(StringRef CheckName, ClangTidyContext *Context);

  /// \brief A simplified version of ClangTidyCheck::diag
  DiagnosticBuilder diag(SourceLocation Loc,
                         DiagnosticIDs::Level Level = DiagnosticIDs::Error);

  bool isC(const LangOptions &LangOpts);

private:
  const std::string CheckName;
};

} // namespace misra
} // namespace tidy
} // namespace clang

#endif // CLANG_TIDY_MISRA_CHECK_H
