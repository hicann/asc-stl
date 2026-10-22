# asc::std::mdspan::empty

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

Header: `<asc/std/mdspan>`.

`asc::std::mdspan::empty` determines whether the current object contains no elements.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Function Prototype

Member of: [`asc::std::mdspan`](mdspan.md).

```cpp
// Excerpt of the declaration inside the asc::std::mdspan class; template parameters and other members are provided by the owning class.
constexpr bool empty() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the object contains no elements, otherwise `false`. |

## Constraints

- This query is provided starting from C++17; for the element access forms and language conditions, see [`mdspan`](mdspan.md#constraints).

- The object is empty when any dimension has an extent of 0; the query only reads the dimension information and does not read the elements pointed to by the data handle.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/mdspan>
#include <asc/std/type_traits>

bool example()
{
    int values[] = {1, 2, 3, 4, 5, 6};
    using Extents = asc::std::extents<asc::std::size_t, 2, 3>;
    asc::std::mdspan<int, Extents> view(values);
    return !view.empty();
}
```

## Related APIs

- [`asc::std::mdspan`](mdspan.md)
- [API list for this header](asc_std_mdspan.md)
