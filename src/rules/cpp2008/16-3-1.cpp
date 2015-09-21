//===--- 16-3-1.cpp - clang-tidy-misra ------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "16-3-1.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/MacroInfo.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/Token.h"

namespace clang {
namespace tidy {
namespace misra {
namespace cpp2008 {

namespace {
class HasCounter : public clang::PPCallbacks {
public:
  HasCounter(Rule_16_3_1 &RuleChecker) : RuleChecker(RuleChecker) {}

  virtual void MacroDefined(const Token &, const MacroDirective *MD) override {
    const MacroInfo *macroInfo = MD->getMacroInfo();
    unsigned int hasCount = 0;

    for (MacroInfo::tokens_iterator I = macroInfo->tokens_begin(),
                                    E = macroInfo->tokens_end();
         I != E; ++I) {
      const std::string tokenType = I->getName();
      // Count occurrences of "hash" and "hashhash"
      if (tokenType.find("hash") == 0) {
        hasCount++;
        // Report only the first illegal hash
        if (hasCount == 2) {
          RuleChecker.diag(I->getLocation());
          break;
        }
      }
    }
  }

private:
  Rule_16_3_1 &RuleChecker;
};
}

Rule_16_3_1::Rule_16_3_1(llvm::StringRef Name, ClangTidyContext *Context)
    : ClangTidyMisraCheck(Name, Context) {}

void Rule_16_3_1::registerPPCallbacksImpl() {
  CI->getPreprocessor().addPPCallbacks(::llvm::make_unique<HasCounter>(*this));
}

} // namespace cpp2008
} // namespace misra
} // namespace tidy
} // namespace clang
