# asc::std::clock

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

Header: `<asc/std/ctime>`.

`asc::std::clock` returns the processor clock tick count of the current execution environment.

Standard semantics reference: [cppreference `ctime`](https://en.cppreference.com/w/cpp/header/ctime).

## Function Prototype

```cpp
namespace asc::std {
clock_t clock() noexcept;
} // namespace asc::std
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `clock_t` | Returns the processor clock tick count of the current execution environment. |

## Constraints

- Host uses the standard clock.
- In AI Core SIMD programming, get_sys_cnt is used; in AI Core SIMT programming, clock64 is used.
- The device-side counter frequency is the 1 GHz declared on this page, and difftime only performs the value computation.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/ctime>

bool example()
{
    const auto value = asc::std::clock();
    return value != static_cast<asc::std::clock_t>(-1);
}
```

## Related APIs

- [API list for this header](asc_std_ctime.md)
