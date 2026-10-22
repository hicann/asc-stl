# asc::std::indirectly_readable_traits::value_type

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

Header: `<asc/std/iterator>`.

`asc::std::indirectly_readable_traits::value_type` identifies the value type of the element or result.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

`value_type` appears only when the readable object type can be determined. The actual selection rules are as follows:

| Input type | `value_type` |
| --- | --- |
| Pointer to object `T*` | `remove_cv_t<T>` |
| Array `T[N]` or `T[]` | The type after removing one array level and the element cv-qualification |
| Class with only the `value_type` member | The object type of that member after removing cv-qualification |
| Class with only the `element_type` member | The object type of that member after removing cv-qualification |
| Class with both members | The object type is provided only if the two are the same after removing cv-qualification; otherwise there is no `value_type` |

The selected result can be queried through the public type:

```cpp
using pointer_value = asc::std::indirectly_readable_traits<int*>::value_type;
using array_value = asc::std::indirectly_readable_traits<const int[3]>::value_type;
```

Other types, or branches where the object type cannot be determined, do not provide this member.

## Constraints

- Provides the C++20 public iterator concepts and traits interfaces.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>
#include <asc/std/type_traits>

bool example()
{
    struct element_holder { using element_type = const long; };
    using pointer_value = asc::std::indirectly_readable_traits<int*>::value_type;
    using array_value = asc::std::indirectly_readable_traits<const int[3]>::value_type;
    using member_value = asc::std::indirectly_readable_traits<element_holder>::value_type;
    static_assert(asc::std::is_same_v<pointer_value, int>);
    static_assert(asc::std::is_same_v<array_value, int>);
    static_assert(asc::std::is_same_v<member_value, long>);
    return true;
}
```

## Related APIs

- [`asc::std::indirectly_readable_traits`](indirectly_readable_traits.md)
- [API list for this header](asc_std_iterator.md)
