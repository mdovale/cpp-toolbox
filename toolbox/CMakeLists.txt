add_library(toolbox INTERFACE)
add_library(toolbox::toolbox ALIAS toolbox)

target_include_directories(
  toolbox
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
)

target_compile_features(toolbox INTERFACE cxx_std_20)

if(TOOLBOX_BUILD_TESTING)
  if(NOT TARGET Catch2::Catch2WithMain)
    message(FATAL_ERROR "toolbox tests require Catch2 (enable TOOLBOX_BUILD_TESTING at the root)")
  endif()

  add_executable(toolbox_tests tests/is_finite_test.cpp)
  target_link_libraries(toolbox_tests PRIVATE toolbox Catch2::Catch2WithMain)
  toolbox_apply_warnings(toolbox_tests)
  toolbox_apply_sanitizers(toolbox_tests)
  catch_discover_tests(toolbox_tests DISCOVERY_MODE PRE_TEST)
endif()
