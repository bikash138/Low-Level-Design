# Precondition Rule (LSP)

## Definition
A precondition is a rule that must be true before a method is called.

Under the Liskov Substitution Principle (LSP), when moving from Parent → Child, the child class must not strengthen the parent’s preconditions. The child may only keep the same precondition or weaken it.

## Example: Password Length
- Parent precondition: Password must be at least 8 characters long.
- To satisfy LSP, the child class must remain fully replaceable wherever the parent is used. This means the child must:
  - keep the same precondition (≥ 8 characters), or
  - weaken it (e.g., ≥ 6 characters)

If the child class tightens the precondition (e.g., “Password must be at least 12 characters long”), then LSP is violated.

## Why Tightening Violates LSP
- Client code written for the parent expects that passwords of length 8 are valid.
- A stricter child would reject such inputs, making it not fully replaceable in place of the parent.
- This breaks substitutability and therefore breaks LSP.

## Quick Comparison
| Parent Rule | Child Rule | LSP Status |
|-------------|------------|------------|
| ≥ 8 chars   | ≥ 8 chars  | OK (same)  |
| ≥ 8 chars   | ≥ 6 chars  | OK (weaker) |
| ≥ 8 chars   | ≥ 12 chars | Violates (stronger) |

## Checklist for Overrides
- Do not add stricter input validation than the parent.
- Allow a superset of inputs accepted by the parent, not a subset.
- Keep documentation of preconditions aligned between parent and child.

