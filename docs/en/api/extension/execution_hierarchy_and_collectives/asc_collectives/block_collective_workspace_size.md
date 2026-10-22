# asc::block_collective_workspace::size

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

`asc::block_collective_workspace::size` returns the number of elements the workspace can hold.

## Function Prototype

```cpp
template<class T> constexpr asc::std::uint32_t asc::block_collective_workspace<T>::size() const noexcept;
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Element type read and written by each participating thread; it determines the size and alignment of the workspace. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::std::uint32_t` | Returns the number of elements the workspace can hold. |

## Constraints

- Can only be called in AI Core SIMT programming.
- The threads of the same block must rendezvous for the call.
- The thread count, dynamic shared UB workspace, and synchronization order must satisfy the declaration requirements, and the workspace must not be reused concurrently during the call.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/collectives>

__aicore__ unsigned int example(unsigned int* dynamic_shared_pointer)
{
    auto workspace = asc::make_block_collective_workspace(dynamic_shared_pointer, 2u);
    return workspace.size();
}
```

## Related APIs

- [API list for this header](asc_collectives.md)
