# AddressSanitizer and UndefinedBehaviorSanitizer.
#
# Call toolbox_enable_sanitizers_directory() from the root before FetchContent
# so Catch2 is instrumented too. toolbox_apply_sanitizers(<target>) is for
# targets added later. TOOLBOX_ENABLE_SANITIZERS is ON in the `sanitize` preset.

function(toolbox_enable_sanitizers_directory)
  if(NOT TOOLBOX_ENABLE_SANITIZERS)
    return()
  endif()

  if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU|AppleClang")
    message(
      WARNING
      "Sanitizers are not applied for compiler '${CMAKE_CXX_COMPILER_ID}'"
    )
    return()
  endif()

  add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
  add_link_options(-fsanitize=address,undefined)
endfunction()

function(toolbox_apply_sanitizers target)
  if(NOT TOOLBOX_ENABLE_SANITIZERS)
    return()
  endif()

  if(NOT TARGET "${target}")
    message(FATAL_ERROR "toolbox_apply_sanitizers: unknown target '${target}'")
  endif()

  if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU|AppleClang")
    return()
  endif()

  target_compile_options(
    "${target}"
    PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer
  )
  target_link_options("${target}" PRIVATE -fsanitize=address,undefined)
endfunction()
