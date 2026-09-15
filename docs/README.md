# Documentation

This directory is the **Sphinx book** source. From the repository root:

```bash
source .venv/bin/activate
pip install -r docs/requirements.txt
./scripts/build-docs.sh          # HTML
./scripts/build-docs.sh --pdf    # HTML + PDF (gate for spine chapters)
```

| File | Role |
|---|---|
| [index.md](index.md) | Preface (Sphinx root) |
| [learning-path.md](learning-path.md) | Contents: chapter numbers and catalog `id`s |
| [notation.md](notation.md) | Frozen symbols, units, dtypes |
| [style.md](style.md) | C++ and prose conventions |
| [build.md](build.md) | CMake, Sphinx, Doxygen, PDF |
| [api.md](api.md) | `toolbox/` API (Breathe) |
| [references.md](references.md) | Bibliography from [refs.bib](refs.bib) |

## Catalog pages

One Markdown file per catalog `id`. They `literalinclude` the matching sources. Do not paste programs here. Spine tutorials are chapters: numbered math or a figure, `{cite}` keys, voice in [style.md](style.md).

| Kind | Directory |
|---|---|
| Tutorial | [tutorials/](tutorials/) |
| How-to | [how-to/](how-to/) |
| Example | [examples/](examples/) |
| Exercise | [exercises/](exercises/) |
| Project | [projects/](projects/) |
| Template | [templates/](templates/) |

Leaf `README.md` files next to code are lab cards (what, when, build, see-also).

Constitution: [../BLUEPRINT.md](../BLUEPRINT.md). How to add a page as part of an entry: [../CONTRIBUTING.md](../CONTRIBUTING.md).
