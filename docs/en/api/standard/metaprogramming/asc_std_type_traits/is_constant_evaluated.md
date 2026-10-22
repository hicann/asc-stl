# asc::std::is_constant_evaluated

## Product Support

<!-- npu="950" id1 -->
- Ascend 950PR&950DT series products: Supported
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3 series products: Not supported
<!-- end id2 -->
<!-- npu="910b" id3 -->
- Atlas A2 series products: Not supported
<!-- end id3 -->
<!-- npu="310b" id4 -->
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas inference series products AI Core: Not supported
<!-- end id5 -->
<!-- npu="310p" id6 -->
- Atlas inference series products Vector Core: Not supported
<!-- end id6 -->
<!-- npu="910" id7 -->
- Atlas training series products: Not supported
<!-- end id7 -->

## Description

Header: `<asc/std/type_traits>`.

`asc::std::is_constant_evaluated` determines whether the current call is during constant evaluation.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Function Prototype

```cpp
namespace asc::std {
[[nodiscard]] constexpr bool is_constant_evaluated() noexcept;
} // namespace asc::std
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds and `false` otherwise. |

## Constraints

- Compiler built-in capability is preferred.
- When the compiler has no corresponding built-in capability, this implementation conservatively returns `false` and cannot recognize constant evaluation; this fallback does not have the full standard detection semantics.

## Example

The following Host example requires the toolchain to provide constant-evaluation detection and checks constant evaluation and an ordinary runtime call separately.

```cpp
#include <asc/std/type_traits>

static_assert(asc::std::is_constant_evaluated());

bool example()
{
    return !asc::std::is_constant_evaluated();
}
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
