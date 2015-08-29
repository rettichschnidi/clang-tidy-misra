# Script shamelessly stolen from the clang/test folder.
# Test runner infrastructure for clang-tidy-misra. This configures the Clang
# test trees for use by Lit, and delegates to LLVM's lit test handlers.

if(CMAKE_CFG_INTDIR STREQUAL ".")
  set(LLVM_BUILD_MODE ".")
else()
  set(LLVM_BUILD_MODE "%(build_mode)s")
endif()

string(REPLACE ${CMAKE_CFG_INTDIR} ${LLVM_BUILD_MODE} CLANG_TIDY_MISRA_TOOLS_DIR ${LLVM_RUNTIME_OUTPUT_INTDIR})

configure_lit_site_cfg(
  ${CMAKE_CURRENT_SOURCE_DIR}/lit.site.cfg.in
  ${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg
  )

option(CLANG_TIDY_MISRA_TEST_USE_VG "Run clang-tidy-misra tests under Valgrind" OFF)
if(CLANG_TIDY_MISRA_TEST_USE_VG)
  set(CLANG_TIDY_MISRA_TEST_EXTRA_ARGS ${CLANG_TIDY_MISRA_TEST_EXTRA_ARGS} "--vg")
endif()

list(APPEND CLANG_TIDY_MISRA_TEST_DEPS
  clang-tidy clang-headers FileCheck
  clangTidyMISRAModule
  )
set(CLANG_TIDY_MISRA_TEST_PARAMS
  clang_site_config=${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg
  )

add_lit_testsuite(check-tidy-misra "Running the clang-tidy-misra tests"
  ${CMAKE_CURRENT_BINARY_DIR}
  PARAMS ${CLANG_TIDY_MISRA_TEST_PARAMS}
  DEPENDS ${CLANG_TIDY_MISRA_TEST_DEPS}
  ARGS ${CLANG_TIDY_MISRA_TEST_EXTRA_ARGS}
  )
set_target_properties(check-tidy-misra PROPERTIES FOLDER "Clang tidy MISRA tests")

#Add dummy library to get Qt Creator to show the tests.
file(GLOB_RECURSE SRC_TEST_LIST "*.c*")
add_library(check-tidy-misra-testfiles STATIC ${SRC_TEST_LIST})
