# cmake/

Reserved for the CMake spine ([docs/build.md](../docs/build.md)):

| Planned file | Role |
|---|---|
| `warnings.cmake` | `-Wall -Wextra -Wpedantic -Werror` for the `dev` preset |
| `sanitizers.cmake` | ASan/UBSan for the `sanitize` preset |
| `toolbox_example.cmake` | `add_toolbox_example()` — one catalog entry, one target |

Do not add a second build system here. Root `CMakeLists.txt` and `CMakePresets.json` are not written yet; this directory exists so that layout is fixed.
