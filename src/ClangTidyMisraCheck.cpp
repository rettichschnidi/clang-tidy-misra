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
    : ClangTidyCheck(CheckName, Context), CheckName(CheckName),
      Context(Context), CI(nullptr) {}

void ClangTidyMisraCheck::registerPPCallbacks(CompilerInstance &Compiler) {
  this->CI = &Compiler;
  registerPPCallbacksSimple();
}

DiagnosticBuilder ClangTidyMisraCheck::diag(SourceLocation Loc,
                                            DiagnosticIDs::Level Level) {
  return ClangTidyCheck::diag(Loc, ruleHeadlines.at(CheckName), Level);
}

bool ClangTidyMisraCheck::isC() const {
  assert(CI && "Need CompilerInstance");
  return (CI->getLangOpts().C99 || CI->getLangOpts().C11);
}

bool ClangTidyMisraCheck::isCPlusPlus() const {
  assert(CI && "Need CompilerInstance");
  return CI->getLangOpts().CPlusPlus;
}

bool ClangTidyMisraCheck::isInSystemHeader(SourceLocation loc) const {
  assert(CI && "Need CompilerInstance");
  const SourceManager &sourceManager = CI->getSourceManager();
  return sourceManager.isInSystemHeader(loc);
}

bool ClangTidyMisraCheck::isBuiltIn(clang::SourceLocation loc) const {
  assert(CI && "Need CompilerInstance");
  const SourceManager &sourceManager = CI->getSourceManager();
  const char *const filename = sourceManager.getPresumedLoc(loc).getFilename();
  return (strcmp(filename, "<built-in>") == 0);
}

bool ClangTidyMisraCheck::isCommandLine(SourceLocation loc) {
  assert(CI && "Need CompilerInstance");
  const SourceManager &sourceManager = CI->getSourceManager();
  const char *const filename = sourceManager.getPresumedLoc(loc).getFilename();
  return (strcmp(filename, "<command line>") == 0);
}

bool ClangTidyMisraCheck::doIgnore(clang::SourceLocation loc) {
  if (loc.isInvalid()) {
    return true;
  }
  if (isBuiltIn(loc)) {
    return true;
  }
  if (isCommandLine(loc)) {
    return true;
  }
  if (isInSystemHeader(loc)) {
    return IgnoreSystemHeaders;
  }

  // Do not check source code locations which are originating from a file.
  auto spellingLocation = CI->getSourceManager().getSpellingLoc(loc);
  auto fileName = CI->getSourceManager().getFilename(spellingLocation);
  if (fileName.empty()) {
    return true;
  }
  return false;
}

} // namespace misra
} // namespace tidy
} // namespace clang
