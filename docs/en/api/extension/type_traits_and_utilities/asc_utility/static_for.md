# asc::static_for

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

Header: `<asc/utility>`.

`asc::static_for` unrolls a zero-based count range or a stepped half-open range at compile time and invokes the callable object once per index, without producing runtime loop dispatch.

## Function Prototype

### Prototype 1

```cpp
namespace asc {
template <auto Size, class Operator, class... Args>
constexpr void static_for(Operator operation, Args&&... args) noexcept(
    noexcept(static_for<decltype(Size), Size>(operation, static_cast<Args&&>(args)...)));
}  // namespace asc
```

### Prototype 2

```cpp
namespace asc {
template <auto Start, decltype(Start) End, decltype(Start) Step = decltype(Start){1}, class Operator, class... Args>
constexpr void static_for(Operator operation, Args&&... args) noexcept(
    noexcept(static_for<decltype(Start), Start, End, Step>(operation, static_cast<Args&&>(args)...)));
}  // namespace asc
```

### Prototype 3

```cpp
namespace asc {
template <class IndexType, IndexType Start, IndexType End, IndexType Step = IndexType{1}, class Operator, class... Args>
constexpr void static_for(Operator operation, Args&&... args) noexcept(
    noexcept(detail::static_for_range<IndexType, Start, End, Step>(operation, static_cast<Args&&>(args)...)));
}  // namespace asc
```

### Prototype 4

```cpp
namespace asc {
template <class SizeType, SizeType Size, class Operator, class... Args>
constexpr void static_for(Operator operation, Args&&... args) noexcept(
    noexcept(detail::static_for_count<SizeType, Size>(operation, static_cast<Args&&>(args)...)));
}  // namespace asc
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Size` | Iteration count of the zero-based unroll (compile-time value); invokes operation exactly once for each index from 0 to Size-1 in order, and performs no invocation when it is non-positive. |
| `Operator` | Type of the callable object operation; must be callable with the compile-time index constant as the first argument, followed by the forwarded args. |
| `Args` | Pack of argument types forwarded to operation at each index invocation (corresponding to the function parameter Args&&...). |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `operation` | Input | Callable object invoked exactly once at each compile-time index; receives the index constant (in integral_constant form, implicitly convertible to the index type) as the first argument, followed by the forwarded args. When used on the device side, its execution space attributes must match those of the caller. |
| `args` | Input/Output | Pack of arguments received by forwarding reference and forwarded as-is to operation at each index invocation; rvalue arguments remain movable, and a moved-from argument is left in a valid but unspecified state. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Start` | Starting index of the half-open iteration range (compile-time value, endpoint included). |
| `End` | Ending index of the half-open iteration range (compile-time value, endpoint excluded). |
| `Step` | Index step (compile-time value, default 1), which must be non-zero; a negative value unrolls in reverse order. |
| `Operator` | Type of the callable object operation; must be callable with the compile-time index constant as the first argument, followed by the forwarded args. |
| `Args` | Pack of argument types forwarded to operation at each index invocation (corresponding to the function parameter Args&&...). |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `operation` | Input | Callable object invoked exactly once at each compile-time index; receives the index constant (in integral_constant form, implicitly convertible to the index type) as the first argument, followed by the forwarded args. When used on the device side, its execution space attributes must match those of the caller. |
| `args` | Input/Output | Pack of arguments received by forwarding reference and forwarded as-is to operation at each index invocation; rvalue arguments remain movable, and a moved-from argument is left in a valid but unspecified state. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `IndexType` | Integer type of the iteration indices; Start, End, and Step are all compile-time values of this type. |
| `Start` | Starting index of the half-open iteration range (compile-time value, endpoint included). |
| `End` | Ending index of the half-open iteration range (compile-time value, endpoint excluded). |
| `Step` | Index step (compile-time value, default 1), which must be non-zero; a negative value unrolls in reverse order. |
| `Operator` | Type of the callable object operation; must be callable with the compile-time index constant as the first argument, followed by the forwarded args. |
| `Args` | Pack of argument types forwarded to operation at each index invocation (corresponding to the function parameter Args&&...). |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `operation` | Input | Callable object invoked exactly once at each compile-time index; receives the index constant (in integral_constant form, implicitly convertible to the index type) as the first argument, followed by the forwarded args. When used on the device side, its execution space attributes must match those of the caller. |
| `args` | Input/Output | Pack of arguments received by forwarding reference and forwarded as-is to operation at each index invocation; rvalue arguments remain movable, and a moved-from argument is left in a valid but unspecified state. |

### Parameters of Prototype 4

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `SizeType` | Integer type of the iteration indices; Size is a compile-time value of this type. |
| `Size` | Iteration count of the zero-based unroll (compile-time value); invokes operation exactly once for each index from 0 to Size-1 in order, and performs no invocation when it is non-positive. |
| `Operator` | Type of the callable object operation; must be callable with the compile-time index constant as the first argument, followed by the forwarded args. |
| `Args` | Pack of argument types forwarded to operation at each index invocation (corresponding to the function parameter Args&&...). |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `operation` | Input | Callable object invoked exactly once at each compile-time index; receives the index constant (in integral_constant form, implicitly convertible to the index type) as the first argument, followed by the forwarded args. When used on the device side, its execution space attributes must match those of the caller. |
| `args` | Input/Output | Pack of arguments received by forwarding reference and forwarded as-is to operation at each index invocation; rvalue arguments remain movable, and a moved-from argument is left in a valid but unspecified state. |

## Return Value

No return value.

## Constraints

- The count form unrolls `[0, Size)` in order; the operation object is not invoked when `Size <= 0`.
- The range form uses a half-open range; `Step` must not be zero, and the index and step arithmetic must be representable; no invocation happens when the direction does not match.
- The operation object must be able to accept each unrolled compile-time index and the given arguments; the operation object in a device-side call must be callable at the same execution location.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/utility>

bool example()
{
    int sum = 0;
    asc::static_for<4>([&](auto index) { sum += index; });
    return sum == 6;
}
```

## Related APIs

- [API list for this header](asc_utility.md)
