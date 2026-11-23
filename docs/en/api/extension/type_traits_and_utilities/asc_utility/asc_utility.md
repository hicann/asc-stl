# Header asc/utility

Provides ordered calls with constant indices (`static_for`) and same-type inclusive numeric interval checks (`in_range`). Callbacks may execute at runtime.

## Usage

```cpp
#include <asc/utility>
```

## API List

| API | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- |
| [asc::in_range](in_range.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::static_for](static_for.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |

## Behavior Changes

The callable is now borrowed, indices use standard `integral_constant`, and supported numeric types are explicit. Code relying on a copied callable, an rvalue-only call operator, or direct user-defined comparisons in `in_range` requires adjustment. See each API page for the exact contract.
