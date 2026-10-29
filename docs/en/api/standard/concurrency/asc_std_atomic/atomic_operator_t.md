# asc::std::atomic::operator T

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

`asc::std::atomic::operator T` is the conversion operator to the stored value type; it atomically loads and returns the stored value with the default memory order, semantically equivalent to calling `load`.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Function Prototype

```cpp
asc::std::atomic::operator T() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the atomically loaded value. |

## Constraints

- Atomic operations can be called in Host and AI Core SIMT programming; atomic objects shared by SIMT threads must be located in GM and initialized before concurrent access.
- The conversion result type is the atomic object's `value_type`, that is, `T`; the conversion reads with `memory_order_seq_cst` and returns the current value.

## Example

The following Host snippet demonstrates the atomic operation; device-side objects must be placed in a valid memory space as specified on this page.

```cpp
#include <asc/std/atomic>

bool example()
{
    asc::std::atomic<int> value{7};
    const int observed = value;
    return observed == 7;
}
```

## Related APIs

- [API list for this header](asc_std_atomic.md)
