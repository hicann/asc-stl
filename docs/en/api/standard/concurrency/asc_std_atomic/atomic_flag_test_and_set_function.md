# asc::std::atomic_flag_test_and_set

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

`asc::std::atomic_flag_test_and_set` sets the atomic flag and returns the previous state.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Function Prototype

```cpp
namespace asc::std {
bool atomic_flag_test_and_set(atomic_flag* object) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `object` | Input/Output | Points to a live atomic object that satisfies the type alignment; this operation modifies its atomic state according to the specified memory order. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` if the condition holds, otherwise `false`. |

## Constraints

- It can be called in Host or AI Core SIMT programming; flag objects shared by SIMT threads must be located in GM and initialized before concurrent access.
- `object` must point to a valid non-volatile [atomic_flag](atomic_flag.md) object.
- This operation atomically sets the flag to `true` and returns the old value; the form without a memory order parameter uses `memory_order_seq_cst`.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/atomic>

decltype(auto) example(asc::std::atomic_flag * object)
{
    return asc::std::atomic_flag_test_and_set(object);
}
```

## Related APIs

- [API list for this header](asc_std_atomic.md)
