# cmake/

CMake modules for the superbuild. Included from the root `CMakeLists.txt`.

| File | Role |
|---|---|
| `warnings.cmake` | `toolbox_apply_warnings()` — `-Wall -Wextra -Wpedantic`; `-Werror` when `TOOLBOX_WARNINGS_AS_ERRORS` |
| `sanitizers.cmake` | `toolbox_apply_sanitizers()` — ASan/UBSan when `TOOLBOX_ENABLE_SANITIZERS` |
| `toolbox_example.cmake` | `add_toolbox_example()` — one catalog lesson, one executable |

Presets: `CMakePresets.json` at the repo root (`dev`, `sanitize`, `docs`). `templates/` are never registered as targets.
