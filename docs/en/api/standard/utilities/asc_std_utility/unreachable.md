# asc::std::unreachable

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

Header: `<asc/std/utility>`.

`asc::std::unreachable` declares that control flow cannot reach the current position; violating the precondition is undefined behavior.

Standard semantics reference: [cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility).

## Function Prototype

```cpp
namespace asc::std {
void unreachable() noexcept;
} // namespace asc::std
```

## Parameters

No parameters.

## Return Value

No return value.

## Constraints

- to_underlying accepts enumeration types only.
- unreachable keeps the standard semantic preconditions but does not add the noreturn attribute, which the current toolchain does not support.

## Example

This interface may be called only when control flow can be proven unreachable. The two boolean branches in the following Host example cover all valid inputs.

```cpp
#include <asc/std/utility>

int choose(bool first)
{
    if (first) return 7;
    if (!first) return 9;
    asc::std::unreachable();
}

bool example()
{
    return choose(true) == 7 && choose(false) == 9;
}
```

## Related APIs

- [API list for this header](asc_std_utility.md)
