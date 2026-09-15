# Register one catalog lesson as one executable.
#
#   add_toolbox_example(NAME <id> DIR <abs-path>)
#   add_toolbox_example(NAME <id> SOURCES <files...> [STD 20])
#
# DIR looks for main.cpp. STD is 20 or 23. templates/ must never be passed here.

function(add_toolbox_example)
  set(options "")
  set(oneValueArgs NAME DIR STD)
  set(multiValueArgs SOURCES)
  cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  if(NOT ARG_NAME)
    message(FATAL_ERROR "add_toolbox_example: NAME is required")
  endif()
  if(ARG_UNPARSED_ARGUMENTS)
    message(
      FATAL_ERROR
      "add_toolbox_example(${ARG_NAME}): unexpected arguments ${ARG_UNPARSED_ARGUMENTS}"
    )
  endif()

  if(ARG_DIR)
    cmake_path(NORMAL_PATH ARG_DIR)
    string(FIND "${ARG_DIR}" "/templates/" _templates_pos)
    if(NOT _templates_pos EQUAL -1)
      message(FATAL_ERROR "add_toolbox_example: templates/ are not in-tree targets")
    endif()
    if(NOT ARG_SOURCES AND EXISTS "${ARG_DIR}/main.cpp")
      set(ARG_SOURCES "${ARG_DIR}/main.cpp")
    endif()
  endif()

  if(NOT ARG_SOURCES)
    message(FATAL_ERROR "add_toolbox_example(${ARG_NAME}): provide DIR or SOURCES")
  endif()

  if(NOT ARG_STD)
    set(ARG_STD 20)
  endif()
  if(NOT ARG_STD STREQUAL "20" AND NOT ARG_STD STREQUAL "23")
    message(FATAL_ERROR "add_toolbox_example(${ARG_NAME}): STD must be 20 or 23")
  endif()

  add_executable("${ARG_NAME}" ${ARG_SOURCES})
  target_link_libraries("${ARG_NAME}" PRIVATE toolbox)
  target_compile_features("${ARG_NAME}" PRIVATE cxx_std_${ARG_STD})
  toolbox_apply_warnings("${ARG_NAME}")
  toolbox_apply_sanitizers("${ARG_NAME}")
endfunction()

# Add every */main.cpp under root_dir as a target named after the folder.
# Tutorial folders may use an NN- prefix; it is stripped from the target name.
function(toolbox_add_lesson_tree root_dir)
  if(NOT IS_DIRECTORY "${root_dir}")
    return()
  endif()

  file(
    GLOB mains
    CONFIGURE_DEPENDS
    "${root_dir}/main.cpp"
    "${root_dir}/*/main.cpp"
    "${root_dir}/*/*/main.cpp"
  )

  foreach(main IN LISTS mains)
    get_filename_component(dir "${main}" DIRECTORY)
    get_filename_component(folder "${dir}" NAME)
    string(REGEX REPLACE "^[0-9][0-9]-" "" name "${folder}")
    if(TARGET "${name}")
      message(
        FATAL_ERROR
        "toolbox_add_lesson_tree: duplicate target '${name}' from ${dir}"
      )
    endif()
    # Every *.cpp in the lesson folder is one executable.
    file(GLOB sources CONFIGURE_DEPENDS "${dir}/*.cpp")
    list(SORT sources)
    add_toolbox_example(NAME "${name}" SOURCES ${sources})
  endforeach()
endfunction()

# Exercises: starter/ and solution/ both compile; target names get a suffix.
function(toolbox_add_exercise_tree root_dir)
  if(NOT IS_DIRECTORY "${root_dir}")
    return()
  endif()

  file(
    GLOB starter_mains
    CONFIGURE_DEPENDS
    "${root_dir}/*/*/starter/main.cpp"
  )
  file(
    GLOB solution_mains
    CONFIGURE_DEPENDS
    "${root_dir}/*/*/solution/main.cpp"
  )

  foreach(main IN LISTS starter_mains)
    get_filename_component(starter_dir "${main}" DIRECTORY)
    get_filename_component(slug_dir "${starter_dir}" DIRECTORY)
    get_filename_component(slug "${slug_dir}" NAME)
    add_toolbox_example(NAME "${slug}-starter" SOURCES "${main}")
  endforeach()

  foreach(main IN LISTS solution_mains)
    get_filename_component(solution_dir "${main}" DIRECTORY)
    get_filename_component(slug_dir "${solution_dir}" DIRECTORY)
    get_filename_component(slug "${slug_dir}" NAME)
    add_toolbox_example(NAME "${slug}-solution" SOURCES "${main}")
  endforeach()
endfunction()
