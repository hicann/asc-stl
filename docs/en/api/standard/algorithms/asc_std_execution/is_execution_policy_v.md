# asc::std::is_execution_policy_v

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

`asc::std::is_execution_policy_v` determines at compile time whether a type is a standard execution policy.

Standard semantics reference: [cppreference `execution`](https://en.cppreference.com/w/cpp/header/execution).

## Declaration

```cpp
namespace asc::std {
template <class T>
inline constexpr const bool is_execution_policy_v = asc::std::is_execution_policy<T>::value;
}  // namespace asc::std
```

## Constraints

- Provides the four execution policy types, objects, and traits.
- The provided algorithm overloads adopt standard-compliant sequential execution semantics.

## Example

The following snippet reads the interface value with concrete template arguments.

```cpp
#include <asc/std/execution>

inline constexpr auto example = asc::std::is_execution_policy_v<asc::std::execution::sequenced_policy>;
static_assert(example);
static_assert(!asc::std::is_execution_policy_v<int>);
```

## Related APIs

- [API list for this header](asc_std_execution.md)
