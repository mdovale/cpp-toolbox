# Cursor configuration

| Path | Role | How it fires |
|---|---|---|
| `AGENTS.md` (repo root and nested) | Map for agents | Always, plus nested files when that tree is in play |
| `rules/` | Persistent constraints | `constitution.mdc` and `conventional-commits.mdc` always; others by glob |
| `skills/` | Procedures | Agent picks them from the description, or `/skill-name` |
| `commands/` | Slash shortcuts | User types `/add-tutorial`, `/review-entry`, … |

Do not duplicate BLUEPRINT here. Skills implement CONTRIBUTING; rules enforce it.

## Commands

| Command | Skill |
|---|---|
| `/add-tutorial` | `add-catalog-entry` (`kind: tutorial`) |
| `/add-howto` | `add-catalog-entry` (`kind: how-to`) |
| `/add-example` | `add-catalog-entry` (`kind: example`) |
| `/add-exercise` | `add-catalog-entry` (`kind: exercise`) |
| `/add-project` | `add-catalog-entry` (`kind: project`) |
| `/add-template` | `add-catalog-entry` (`kind: template`) |
| `/review-entry` | `review-catalog-entry` |
| `/extract-toolbox` | `extract-to-toolbox` |
