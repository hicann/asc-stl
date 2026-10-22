# asc::warp_all

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

Header: `<asc/warp>`.

`asc::warp_all` determines whether the predicates of all active lanes in the current warp are true.

## Function Prototype

```cpp
namespace asc {
bool warp_all(bool predicate) noexcept;
}  // namespace asc
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `predicate` | Input | The bool voting value already evaluated by this lane or thread; the interface collectively processes this value directly and does not call a predicate function. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, otherwise `false`. |

## Constraints

- Can only be called in AI Core SIMT programming.
- All participating active threads must call it in converged control flow.

## Example

The following snippet focuses on calling this interface; inputs, resources, and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/warp>

__aicore__ decltype(auto) example(bool predicate)
{
    return asc::warp_all(predicate);
}
```

The corresponding complete project uses `C++17`; compile and run it on the target toolchain and device.

Complete example source:

- [CMakeLists.txt](../../../../../zh/examples/warp_collectives/CMakeLists.txt)
- [warp_example.h](../../../../../zh/examples/warp_collectives/warp_example.h)
- [kernel.asc](../../../../../zh/examples/warp_collectives/kernel.asc)
- [main.cpp](../../../../../zh/examples/warp_collectives/main.cpp)

## Related APIs

- [API list for this header](asc_warp.md)
