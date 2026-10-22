# asc::std::crend

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

`asc::std::crend` obtains the constant one-past-the-end iterator of the reversed range.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

```cpp
namespace asc::std {
template<class C> constexpr auto crend(const C& c) noexcept(noexcept(::asc::std::rend(c))) -> decltype(asc::std::rend(c));
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `C` | The type of the array or container being queried; it must provide the corresponding range access operations. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `c` | Input | Reference to the object used by "obtains the constant one-past-the-end iterator of the reversed range"; the referenced object must remain valid for the duration of the call. |

## Return Value

| Return type | Description |
| --- | --- |
| `decltype(asc::std::rend(c))` | Returns the constant one-past-the-end iterator of the reversed range. |

## Constraints

- Supports non-I/O ranges, arrays, and user containers.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {1, 2, 3, 4};
    auto last = asc::std::crend(values);
    return last.base() == values && last - asc::std::crbegin(values) == 4;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
