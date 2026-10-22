# asc::std::execution::par

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

Header: `<asc/std/execution>`.

`asc::std::execution::par` denotes the parallel policy form; in the current version, the corresponding overloads use a sequential execution path.

Standard semantics reference: [cppreference `execution`](https://en.cppreference.com/w/cpp/header/execution).

## Declaration

```cpp
namespace asc::std::execution {
inline constexpr const parallel_policy par;
}  // namespace asc::std::execution
```

## Constraints

- Provides the four execution policy types, objects, and traits.
- The provided algorithm overloads adopt standard-compliant sequential execution semantics.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/execution>

auto value = asc::std::execution::par;
```

## Related APIs

- [API list for this header](asc_std_execution.md)
