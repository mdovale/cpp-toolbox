cmake_minimum_required(VERSION 3.21)

project(
  cpp-toolbox
  VERSION 0.1.0
  DESCRIPTION "Modern C++ catalog for engineers and scientists"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(TOOLBOX_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)
option(TOOLBOX_ENABLE_SANITIZERS "Enable ASan and UBSan" OFF)
option(TOOLBOX_BUILD_TESTING "Build toolbox tests (Catch2)" ON)
option(
  TOOLBOX_BUILD_EXAMPLES
  "Build how-tos, examples, exercise starters/solutions, and projects"
  OFF
)

option(
  TOOLBOX_BUILD_DOCS
  "Add docs-html and docs-pdf custom targets (needs Sphinx + Doxygen)"
  OFF
)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/warnings.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/sanitizers.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/toolbox_example.cmake")
toolbox_enable_sanitizers_directory()

if(TOOLBOX_BUILD_TESTING)
  include(FetchContent)
  set(CATCH_BUILD_TESTING OFF CACHE BOOL "" FORCE)
  set(CATCH_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(CATCH_INSTALL_DOCS OFF CACHE BOOL "" FORCE)
  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.1
    GIT_SHALLOW TRUE
  )
  FetchContent_MakeAvailable(Catch2)
  list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/extras")
  include(CTest)
  include(Catch)
endif()

add_subdirectory(toolbox)

# Planned catalog rows have no folder yet; missing trees are skipped.
toolbox_add_lesson_tree("${CMAKE_SOURCE_DIR}/tutorials")

if(TOOLBOX_BUILD_EXAMPLES)
  toolbox_add_lesson_tree("${CMAKE_SOURCE_DIR}/how-to")
  toolbox_add_lesson_tree("${CMAKE_SOURCE_DIR}/examples")
  toolbox_add_lesson_tree("${CMAKE_SOURCE_DIR}/projects")
  toolbox_add_exercise_tree("${CMAKE_SOURCE_DIR}/exercises")
endif()

if(TOOLBOX_BUILD_DOCS)
  find_package(Python3 COMPONENTS Interpreter REQUIRED)
  find_program(DOXYGEN_EXECUTABLE doxygen REQUIRED)
  execute_process(
    COMMAND "${Python3_EXECUTABLE}" -c "import sphinx, breathe, myst_parser"
    RESULT_VARIABLE _toolbox_sphinx_ok
  )
  if(NOT _toolbox_sphinx_ok EQUAL 0)
    message(
      FATAL_ERROR
      "TOOLBOX_BUILD_DOCS needs Sphinx in ${Python3_EXECUTABLE} "
      "(pip install -r docs/requirements.txt)"
    )
  endif()

  add_custom_target(
    docs-html
    COMMAND
      "${Python3_EXECUTABLE}" -m sphinx -W -b html
      "${CMAKE_SOURCE_DIR}/docs" "${CMAKE_SOURCE_DIR}/docs/_build/html"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    COMMENT "Sphinx HTML"
    VERBATIM
  )
  add_custom_target(
    docs-pdf
    COMMAND
      "${Python3_EXECUTABLE}" -m sphinx -W -b latex
      "${CMAKE_SOURCE_DIR}/docs" "${CMAKE_SOURCE_DIR}/docs/_build/latex"
    COMMAND
      "${CMAKE_COMMAND}" -E chdir "${CMAKE_SOURCE_DIR}/docs/_build/latex"
      latexmk -pdf -interaction=nonstopmode cpp-toolbox.tex
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    COMMENT "Sphinx PDF"
    VERBATIM
  )
endif()
