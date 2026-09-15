# toolbox

Small **header-only** core used by some catalog entries. It is optional: a reader must still understand an example that does not include it.

## Public headers

| Header | Role |
|---|---|
| [`<toolbox/is_finite.hpp>`](include/toolbox/is_finite.hpp) | `toolbox::is_finite(double)` — reject inf/NaN before a meaningless reduction |

Includes look like `#include <toolbox/is_finite.hpp>`.

## Rules

- Headers live in `include/toolbox/`.
- Promote a helper here only after it has been copied about three times ([BLUEPRINT.md](../BLUEPRINT.md)).
- Do not become a framework. No required base classes, no “app” runtime, no hidden global state.
- Doxygen documents every public entity. Tests live in `tests/` (Catch2).

```bash
cmake --preset dev
cmake --build --preset dev --target toolbox_tests
ctest --preset dev
```
