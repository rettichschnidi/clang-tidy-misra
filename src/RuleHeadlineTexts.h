//===-  RuleHeadlineTexts.h - clang-tidy-misra ----------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef CLANG_TIDY_MISRA_RULE_HEADLINE_TEXTS_H
#define CLANG_TIDY_MISRA_RULE_HEADLINE_TEXTS_H

#include <string>
#include <unordered_map>

namespace clang {
namespace tidy {
namespace misra {

using HeadlineByRuleName = std::unordered_map<std::string, std::string>;

/// \brief Map containing the headline of each MISRA rule.
extern const HeadlineByRuleName ruleHeadlines;

} // namespace misra
} // namespace tidy
} // namespace clang

#endif // CLANG_TIDY_MISRA_RULE_HEADLINE_TEXTS_H
