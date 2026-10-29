# asc::block_collective_workspace_bytes

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

Header: `<asc/collectives>`.

`asc::block_collective_workspace_bytes` computes the number of workspace bytes required by a block collective operation for the specified thread count.

This interface is available in AI Core SIMT programming.

## Function Prototype

```cpp
namespace asc {
template<class T> constexpr asc::std::size_t block_collective_workspace_bytes(asc::std::uint32_t thread_count) noexcept;
} // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Element type read and written by each participating thread; it determines the size and alignment of the workspace. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `thread_count` | Input | Number of elements participating in the operation. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::std::size_t` | Returns the number of workspace bytes required by a collective operation for the specified thread count. |

## Constraints

- T can only be int32_t, uint32_t, or float.
- thread_count must be a multiple of 32 and within the range [32, 1024].

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/collectives>
#include <asc/std/cstddef>

__aicore__ asc::std::size_t example()
{
    // 64 participating threads form two warps and require two unsigned integers.
    return asc::block_collective_workspace_bytes<unsigned int>(64u);
}
```

## Related APIs

- [API list for this header](asc_collectives.md)
