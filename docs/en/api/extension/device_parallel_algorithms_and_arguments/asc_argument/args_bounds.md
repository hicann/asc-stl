# asc::args::bounds

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

Header: `<asc/argument>`.

`asc::args::bounds` creates a compile-time or runtime argument bounds object.

## Function Prototype

### Prototype 1

```cpp
namespace asc::args {
template <auto Lower, auto Upper>
constexpr asc::args::static_bounds<Lower, Upper> bounds() noexcept;
}  // namespace asc::args
```

### Prototype 2

```cpp
namespace asc::args {
template <class T>
constexpr asc::args::runtime_bounds<T> bounds(T lower, T upper) noexcept;
}  // namespace asc::args
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Lower` | Compile-time lower bound: serves as the lower() of static_bounds<Lower, Upper>; requires Lower ≤ Upper. |
| `Upper` | Compile-time upper bound: serves as the upper() of static_bounds<Lower, Upper>. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Type of the runtime bound values. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `lower` | Input | Runtime lower bound: stored into the returned runtime_bounds<T> and queried through lower(). |
| `upper` | Input | Runtime upper bound: stored into the returned runtime_bounds<T> and queried through upper(). |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `asc::args::static_bounds<Lower, Upper>` | Returns a compile-time or runtime argument bounds object. |
| Prototype 2 | `asc::args::runtime_bounds<T>` | Returns a compile-time or runtime argument bounds object. |

## Constraints

- Runtime bounds are stored by value, and the caller must ensure that lower is not greater than upper; construction and queries perform no argument range check. For compile-time bounds, Lower must not be greater than Upper.

- Uses C++17 and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following snippet provides concrete template arguments and the objects to call.

```cpp
#include <asc/argument>

decltype(auto) example()
{
    return asc::args::bounds<0, 10>();
}
```

## Related APIs

- [API list for this header](asc_argument.md)
