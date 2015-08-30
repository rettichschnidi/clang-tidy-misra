//===--- BannedInclude.h - clang-tidy-misra -------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef BANNED_INCLUDE_H
#define BANNED_INCLUDE_H

#include "clang/Lex/Preprocessor.h"
#include <string>
#include <unordered_set>

namespace clang {
namespace tidy {
namespace misra {
namespace common {

template <typename Checker> class BannedInclude : public PPCallbacks {
public:
  using StringSet = std::unordered_set<std::string>;
  BannedInclude(Checker &RuleChecker, StringSet &&SetOfBannedIncludes)
      : PPCallbacks(), RuleChecker(RuleChecker),
        SetOfBannedIncludes(SetOfBannedIncludes) {}

  virtual void
  InclusionDirective(SourceLocation HashLoc, const Token &IncludeTok,
                     llvm::StringRef FileName, bool IsAngled,
                     CharSourceRange FilenameRange, const FileEntry *File,
                     llvm::StringRef SearchPath, llvm::StringRef RelativePath,
                     const Module *Imported) override {
    if (SetOfBannedIncludes.count(FileName) > 0) {
      RuleChecker.diag(HashLoc);
    }
  }

private:
  Checker &RuleChecker;
  const StringSet SetOfBannedIncludes;
};

} // namespace common
} // namespace misra
} // namespace tidy
} // namespace clang

#endif // BANNED_INCLUDE_H
