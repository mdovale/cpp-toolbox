# Compiler warnings for cpp-toolbox targets.
#
# Apply with toolbox_apply_warnings(<target>).
# TOOLBOX_WARNINGS_AS_ERRORS is ON in the `dev` preset.

function(toolbox_apply_warnings target)
  if(NOT TARGET "${target}")
    message(FATAL_ERROR "toolbox_apply_warnings: unknown target '${target}'")
  endif()

  if(MSVC)
    target_compile_options("${target}" PRIVATE /W4)
    if(TOOLBOX_WARNINGS_AS_ERRORS)
      target_compile_options("${target}" PRIVATE /WX)
    endif()
    return()
  endif()

  target_compile_options("${target}" PRIVATE -Wall -Wextra -Wpedantic)

  # AppleClang + recent SDKs warn that MACOSX_DEPLOYMENT_TARGET does not
  # match the SDK. That noise becomes a hard error under -Werror.
  if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    target_compile_options(
      "${target}" PRIVATE -Wno-overriding-deployment-version
    )
  endif()

  if(TOOLBOX_WARNINGS_AS_ERRORS)
    target_compile_options("${target}" PRIVATE -Werror)
  endif()
endfunction()
