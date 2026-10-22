# asc::std::is_execution_policy

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

`asc::std::is_execution_policy` marks a standard execution policy form; the actual execution path is subject to the constraints on this page.

Standard semantics reference: [cppreference `execution`](https://en.cppreference.com/w/cpp/header/execution).

## Declaration

```cpp
namespace asc::std {
template<class T> struct is_execution_policy;
} // namespace asc::std
```

## Constraints

- Provides the four execution policy types, objects, and traits.
- The provided algorithm overloads adopt standard-compliant sequential execution semantics.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/execution>

bool example()
{
    static_assert(asc::std::is_execution_policy<asc::std::execution::sequenced_policy>::value);
    static_assert(!asc::std::is_execution_policy<int>::value);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_execution.md)
