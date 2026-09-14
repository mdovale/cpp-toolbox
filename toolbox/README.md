# toolbox

Small **header-only** core used by some catalog entries. It is optional: a reader must still understand an example that does not include it.

## Rules

- Headers live in `include/toolbox/` and are included as `#include <toolbox/....hpp>`.
- Promote a helper here only after it has been copied about three times ([BLUEPRINT.md](../BLUEPRINT.md)).
- Do not become a framework. No required base classes, no “app” runtime, no hidden global state.
- Doxygen documents every public entity. Tests will live in `tests/` once Catch2 is wired up.

There are no headers yet. The first header should arrive with a test in the same change as the CMake spine, or as a third-copy extraction.
