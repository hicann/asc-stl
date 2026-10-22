# asc::std::atomic_flag::test

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

`asc::std::atomic_flag::test` reads whether the atomic flag is currently set.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Function Prototype

Member of: [`asc::std::atomic_flag`](atomic_flag.md).

```cpp
// Excerpt of the declaration inside the asc::std::atomic_flag class; template parameters and other members are provided by the enclosing class.
bool test(memory_order order = memory_order_seq_cst) const noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `order` | Input | The memory order used to read the flag, determining the visibility order of this read; it can only take relaxed, consume, acquire, or seq_cst. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` if the condition holds, otherwise `false`. |

## Constraints

- It can be called in Host or AI Core SIMT programming; flag objects shared by SIMT threads must be located in GM and initialized before concurrent access.
- The memory order must be `memory_order_relaxed`, `memory_order_consume`, `memory_order_acquire`, or `memory_order_seq_cst`; `memory_order_release` and `memory_order_acq_rel` are not allowed.

## Example

The following Host snippet demonstrates the atomic operation; device-side objects must be placed in a valid memory space as specified on this page.

```cpp
#include <asc/std/atomic>

decltype(auto) example(const asc::std::atomic_flag& flag)
{
    return flag.test(asc::std::memory_order_relaxed);
}
```

## Related APIs

- [`asc::std::atomic_flag`](atomic_flag.md)
- [API list for this header](asc_std_atomic.md)
