# asc::std::size

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

`asc::std::size` obtains the number of elements in a range.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class Cont> constexpr auto size(const Cont& value) noexcept(noexcept(value.size())) -> decltype(value.size());
} // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template<class T, size_t Sz> constexpr size_t size(const T (&value)[Sz]) noexcept;
} // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Cont` | The container type; it must provide a size() member. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The container whose element count is measured; the return type and value of its `size()` member are preserved, without unsigned conversion. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The element type of the array. |
| `Sz` | The array length, a compile-time constant. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The array whose element count is measured; returns its length Sz. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `decltype(value.size())` | Returns the number of elements in the range. |
| Prototype 2 | `size_t` | Returns the number of elements in the range. |

## Constraints

- Supports non-I/O ranges, arrays, and user containers.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>
#include <asc/std/type_traits>

bool example()
{
    struct signed_size_container {
        constexpr int size() const noexcept { return 3; }
    };
    signed_size_container container;
    static_assert(asc::std::is_same_v<decltype(asc::std::size(container)), int>);
    return asc::std::size(container) == 3;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
