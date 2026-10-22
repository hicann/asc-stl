# asc::std::atomic::compare_exchange_strong

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

`asc::std::atomic::compare_exchange_strong` compares the current value with expected; if they are equal it writes desired, otherwise it updates expected.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Function Prototype

Member of: [`asc::std::atomic`](atomic.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside the asc::std::atomic class; template parameters and other members are provided by the enclosing class.
bool compare_exchange_strong(T& expected, T desired, memory_order success) noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside the asc::std::atomic class; template parameters and other members are provided by the enclosing class.
bool compare_exchange_strong(T& expected, T desired, memory_order success, memory_order failure) noexcept;
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `expected` | Input/Output | Provides the expected value or target value; on comparison failure the function writes the observed current atomic value into `expected`; the strong form does not allow spurious failure, while the weak form allows spurious failure (it may return `false` even when the values are equal). |
| `desired` | Input | The target value written into the atomic object when the comparison is equal. |
| `success` | Input | The memory order used by the success branch of the compare-exchange, constraining the visibility order of the exchange write. |
### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `expected` | Input/Output | Provides the expected value or target value; on comparison failure the function writes the observed current atomic value into `expected`; the strong form does not allow spurious failure, while the weak form allows spurious failure (it may return `false` even when the values are equal). |
| `desired` | Input | The target value written into the atomic object when the comparison is equal. |
| `success` | Input | The memory order used by the success branch of the compare-exchange, constraining the visibility order of the exchange write. |
| `failure` | Input | The memory order used by the failure branch (read-only) of the compare-exchange; it must not be release or acq_rel, and must not be stronger than success. |
## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `bool` | Returns `true` if the condition holds, otherwise `false`. |
| Prototype 2 | `bool` | Returns `true` if the condition holds, otherwise `false`. |

## Constraints

- Atomic operations can be called in Host and AI Core SIMT programming; atomic objects shared by SIMT threads must be located in GM and initialized before concurrent access.
- On comparison failure the observed current value is written back to `expected`; the caller must provide a writable expected-value object that remains valid for the duration of the call.
- In the two-memory-order-parameter form, `failure` must not be `memory_order_release` or `memory_order_acq_rel`, and must not be stronger than the success memory order.

## Example

The following Host snippet demonstrates the atomic operation; device-side objects must be placed in a valid memory space as specified on this page.

```cpp
#include <asc/std/atomic>

decltype(auto) example(asc::std::atomic<int>& value)
{
    int expected = 1;
    return value.compare_exchange_strong(expected, 2, asc::std::memory_order_relaxed);
}
```

## Related APIs

- [`asc::std::atomic`](atomic.md)
- [API list for this header](asc_std_atomic.md)
