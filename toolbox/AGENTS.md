# Agent map — toolbox/

You are in the shared header-only core.

- Put public headers in `include/toolbox/` as `toolbox/<name>.hpp`.
- Include them as `#include <toolbox/....hpp>`.
- Do not add a helper because one example wants it. Extract under pressure (about three copies) using the `extract-to-toolbox` skill.
- Document with Doxygen. Every new header needs a test once Catch2 exists.
- Entries must remain readable if this header is deleted; toolbox is a convenience.
