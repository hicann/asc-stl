# asc::std::midpoint

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

Header: `<asc/std/numeric>`.

`asc::std::midpoint` computes the midpoint while avoiding unnecessary overflow. The integer overload rounds toward the first argument.

Standard semantics reference: [cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class Fp> constexpr enable_if_t<is_floating_point_v<Fp>, Fp> midpoint(Fp left, Fp right) noexcept;
} // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template<class T, enable_if_t<is_object_v<T>&& !is_void_v<T>&& (sizeof(T) > 0), int> = 0> constexpr T* midpoint(T* left, T* right) noexcept;
} // namespace asc::std
```

### Prototype 3

```cpp
namespace asc::std {
template<class T> constexpr enable_if_t<is_integral_v<T>&& !is_same_v<bool, T>&& !is_null_pointer_v<T>, T> midpoint(T left, T right) noexcept;
} // namespace asc::std
```

## Parameters

The unnamed template constraint parameters in the declarations are used to select the available overloads and need not be provided by the caller; for the applicable types and call conditions of the interface, see the Constraints section.

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Fp` | The floating-point type of the endpoints and the midpoint result. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The left floating-point endpoint for computing the midpoint. |
| `right` | Input | The right floating-point endpoint for computing the midpoint. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The type of the objects pointed to by `left` and `right`; must be an object type other than void. |
**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The left object pointer endpoint for computing the midpoint; should point into the same array as `right` or to its past-the-end position. |
| `right` | Input | The right object pointer endpoint for computing the midpoint; should point into the same array as `left` or to its past-the-end position. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The integer type of the endpoints and the midpoint result; excludes bool. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The left integer endpoint for computing the midpoint. |
| `right` | Input | The right integer endpoint for computing the midpoint. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `Fp` | Returns the midpoint of the two floating-point values. |
| Prototype 2 | `T *` | Returns a pointer to the element at the midpoint between the two pointers. |
| Prototype 3 | `T` | Returns the midpoint of the two integers. |

## Constraints

- Integer, floating-point, and object pointer overloads are provided; no execution policy overload is provided.
- The two arguments of the integer overload may have the same or opposite signs.
- The integer overload computes the midpoint through an unsigned difference, so the result is not distorted by overflow of the intermediate `left + right` quantity.
- The two arguments of the pointer overload must point to elements within the same array object or to its past-the-end position; otherwise the behavior is undefined.

## Example

The following Host example uses a concrete object and checks the result of the call.

```cpp
#include <asc/std/numeric>

bool example()
{
    int values[5] = {};
    return asc::std::midpoint(-3, 3) == 0 &&
        asc::std::midpoint(values, values + 4) == values + 2;
}
```

## Related APIs

- [API list for this header](asc_std_numeric.md)
