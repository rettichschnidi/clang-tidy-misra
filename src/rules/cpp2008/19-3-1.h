//===--- 19-3-1.h - clang-tidy-misra --------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef CLANG_TIDY_MISRA_CPP_2008_RULE_19_3_1_H
#define CLANG_TIDY_MISRA_CPP_2008_RULE_19_3_1_H

#include "ClangTidyMisraCheck.h"

namespace clang {
namespace tidy {
namespace misra {
namespace cpp2008 {

class Rule_19_3_1 : public ClangTidyMisraCheck {
public:
  Rule_19_3_1(StringRef Name, ClangTidyContext *Context);
  void registerPPCallbacksSimple() override;
};

} // cpp2008
} // namespace misra
} // namespace tidy
} // namespace clang

#endif // CLANG_TIDY_MISRA_CPP_2008_RULE_19_3_1_H
