# asc::std::to_array

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

`asc::std::to_array` constructs an array with the corresponding element type and length from a built-in array.

Standard semantics reference: [cppreference `array`](https://en.cppreference.com/w/cpp/header/array).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<typename T, size_t Size> constexpr array<remove_cv_t<T>, Size> to_array(T (&&source)[Size]) noexcept(is_nothrow_move_constructible_v<T>);
} // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template<typename T, size_t Size> constexpr array<remove_cv_t<T>, Size> to_array(T (&source)[Size]) noexcept(is_nothrow_constructible_v<T, T&>);
} // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The element type of the source built-in array; the result element type is `remove_cv_t<T>`. |
| `Size` | The number of elements of the input built-in array, deduced from the array type; the resulting `asc::std::array` has the same number of elements. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `source` | Input/Output | An rvalue built-in array; the returned `array` is move-constructed element by element, and the subsequent state of the source elements is determined by the move construction semantics of `T`. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The element type of the source built-in array; the result element type is `remove_cv_t<T>`. |
| `Size` | The number of elements of the input built-in array, deduced from the array type; the resulting `asc::std::array` has the same number of elements. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `source` | Input | An lvalue built-in array; the elements of the returned `array` are constructed from the corresponding source elements. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `array<remove_cv_t<T>, Size>` | Returns an `array` object whose element type is deduced from the input array and whose length is unchanged. |
| Prototype 2 | `array<remove_cv_t<T>, Size>` | Returns an `array` object whose element type is deduced from the input array and whose length is unchanged. |

## Constraints

- Both the lvalue and rvalue array overloads are provided starting from C++17.
- `Size` is deduced from the length of the source built-in array. In standard C++ the length of a built-in array must be greater than 0; multidimensional arrays are not accepted, i.e. `T` cannot still be an array type.
- Prototype 1 requires `is_move_constructible_v<T>` to be `true`; prototype 2 requires `is_constructible_v<T, T&>` to be `true`. Elements are not required to be default constructible.
- Prototype 1 is `noexcept` only when `is_nothrow_move_constructible_v<T>` is `true`; prototype 2 is `noexcept` only when `is_nothrow_constructible_v<T, T&>` is `true`. Element constructions used on the device side must not throw.
- The returned `array` has its own element storage; the validity of pointers, references, or other resources held by the elements themselves is still determined by the semantics of `T`.

## Example

The following Host example uses a concrete object and checks the result of the call.

```cpp
#include <asc/std/array>

bool example()
{
    int source[2] = {2, 4};
    const auto result = asc::std::to_array(source);
    source[0] = 9;
    return result.size() == 2 && result[0] == 2 && result[1] == 4;
}
```

## Related APIs

- [API list for this header](asc_std_array.md)
