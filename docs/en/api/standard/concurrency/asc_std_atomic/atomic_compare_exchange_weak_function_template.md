# asc::std::atomic_compare_exchange_weak

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

Header: `<asc/std/atomic>`.

`asc::std::atomic_compare_exchange_weak` attempts to compare and exchange the current value and is allowed to report spurious failure to fit retry loops; the memory order and address space must satisfy the restrictions on this page.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Function Prototype

```cpp
namespace asc::std {
template<class T> bool atomic_compare_exchange_weak(atomic<T>* object, T* expected, T desired) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The value type stored by the atomic object. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `object` | Input/Output | Points to a live atomic object that satisfies the type alignment; this operation modifies its atomic state according to the specified memory order. |
| `expected` | Input/Output | Provides the address of the expected value or target value; on comparison failure the function writes the observed current atomic value into `*expected`; the weak form allows spurious failure (it may return `false` even when the values are equal), while the strong form does not allow spurious failure. |
| `desired` | Input | The target value written into the atomic object when the comparison is equal. |
## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the exchange is completed; returns `false` on comparison failure or spurious failure (which can occur even when the values are equal). |

## Constraints

- Atomic operations can be called in Host and AI Core SIMT programming; atomic objects shared by SIMT threads must be located in GM and initialized before concurrent access.
- `object` must point to a valid [atomic](atomic.md) object whose value type must match the template parameter `T`.
- On comparison failure the observed current value is written back to `expected`; the caller must provide a writable expected-value object that remains valid for the duration of the call.

## Example

The following Host snippet uses a concrete integer atomic object; device-side objects must be located in accessible global memory.

```cpp
#include <asc/std/atomic>

decltype(auto) example()
{
    asc::std::atomic<int> value{1};
    int expected = 1;
    return asc::std::atomic_compare_exchange_weak(&value, &expected, 2);
}
```

## Related APIs

- [API list for this header](asc_std_atomic.md)
