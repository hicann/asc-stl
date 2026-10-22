# asc::std::array

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

Header: `<asc/std/array>`.

`asc::std::array` contiguously stores a fixed number of elements determined at compile time.

Standard semantics reference: [cppreference `array`](https://en.cppreference.com/w/cpp/header/array).

## Declaration

```cpp
namespace asc::std {
template<class T, size_t Size> struct array;
template<class T> struct array<T, 0>;
} // namespace asc::std
```

## Constraints

- `Size` is the number of elements determined at compile time and can be `0`. When `Size == 0`, there are no accessible elements, and the subscript, `front`, `back`, or `get` cannot be used to access elements.
- When `Size > 0`, `T` must be usable as the element type of a built-in array; operations such as fill, comparison, and swap additionally require `T` to support the corresponding element operations.
- The element storage is located inside the `array` object and is not dynamically allocated by the container; the resource operations of the element type itself are still determined by `T`.
- The exception specification is subject to the declaration of each operation. For example, `fill` for a non-empty array is not declared `noexcept`, and whether the member `swap` is `noexcept` depends on whether the elements can be swapped without throwing. Element operations used on the device side must not throw.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/array>

bool example()
{
    asc::std::array<int, 3> values{{1, 2, 3}};
    values[1] = 7;
    return values.size() == 3 && values.front() == 1 && values[1] == 7 && values.back() == 3;
}
```

## Related APIs

- [API list for this header](asc_std_array.md)
