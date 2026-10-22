# asc::std::integer_sequence

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

`asc::std::integer_sequence` holds a compile-time integer sequence in a type.

Standard semantics reference: [cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility).

## Declaration

```cpp
namespace asc::std {
template<class T, T ...Index> struct integer_sequence;
} // namespace asc::std
```

## Constraints

- Provides the complete standard form.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/utility>
#include <asc/std/type_traits>

bool example()
{
    using sequence = asc::std::integer_sequence<int, 2, 4, 6>;
    static_assert(sequence::size() == 3);
    static_assert(asc::std::is_same_v<typename sequence::value_type, int>);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_utility.md)
