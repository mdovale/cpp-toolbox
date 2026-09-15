# Tests for `toolbox`

Catch2 tests for `toolbox/include/toolbox/` headers. The binary is `toolbox_tests`.

```bash
cmake --preset dev
cmake --build --preset dev --target toolbox_tests
ctest --preset dev --output-on-failure
```

Add a `*_test.cpp` here in the same change as a new public header.
