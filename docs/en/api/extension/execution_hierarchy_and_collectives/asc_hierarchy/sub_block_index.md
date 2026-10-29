# asc::sub_block_index

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

Header: `<asc/hierarchy>`.

`asc::sub_block_index` returns the sub-block index of the current execution unit.

## Function Prototype

```cpp
namespace asc {
unsigned int sub_block_index() noexcept;
} // namespace asc
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `unsigned int` | Returns the index of the current execution unit within its level. |

## Constraints

- Can only be called in AI Core SIMD programming.
- The parameter types, address spaces, value ranges, and object lifetimes must satisfy the declaration on this page.

## Example

This SIMD kernel writes one entry for each sub-block of each AI Core block. The caller must provide valid GM output for at least the AI Core block count times the actual sub-block count unsigned int values and read it back after kernel completion. Each AI Core block contributes consecutive entries from 0 through its sub-block count minus one. This query is available only in SIMD; the documentation gate checks actual SIMD compilation, not successful NPU execution.

```cpp
#include <asc/hierarchy>

__global__ __vector__ void example(__gm__ unsigned int* output)
{
    const auto block = asc::block_index();
    const auto sub_blocks = asc::sub_block_count();
    const auto sub_block = asc::sub_block_index();
    output[block * sub_blocks + sub_block] = asc::sub_block_index();
}
```

## Related APIs

- [API list for this header](asc_hierarchy.md)
