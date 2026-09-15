cmake_minimum_required(VERSION 3.21)

# Copy-out CMake for this folder. The cpp-toolbox superbuild does not
# add_subdirectory this file; toolbox_add_lesson_tree compiles every
# *.cpp here into the target cmake-app (the 03- prefix is stripped).
project(cmake-app LANGUAGES CXX)

add_executable(cmake-app main.cpp peak_volts.cpp)
target_compile_features(cmake-app PRIVATE cxx_std_20)
