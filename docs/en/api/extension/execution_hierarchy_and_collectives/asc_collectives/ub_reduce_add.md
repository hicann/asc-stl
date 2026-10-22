# asc::ub_reduce_add

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

`asc::ub_reduce_add` sums the elements in a contiguous UB range.

## Function Prototype

### Prototype 1

```cpp
namespace asc {
asc::std::int32_t ub_reduce_add(asc::ub_span<const asc::std::int32_t> input) noexcept;
}  // namespace asc
```

### Prototype 2

```cpp
namespace asc {
asc::std::uint32_t ub_reduce_add(asc::ub_span<const asc::std::uint32_t> input) noexcept;
}  // namespace asc
```

### Prototype 3

```cpp
namespace asc {
float ub_reduce_add(asc::ub_span<const float> input) noexcept;
}  // namespace asc
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `input` | Input | Non-owning view of a contiguous region of the on-chip buffer; the underlying storage must remain valid during the operation. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `input` | Input | Non-owning view of a contiguous region of the on-chip buffer; the underlying storage must remain valid during the operation. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `input` | Input | Non-owning view of a contiguous region of the on-chip buffer; the underlying storage must remain valid during the operation. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `asc::std::int32_t` | Returns the result of reducing the participating threads or the contiguous range according to the interface name. |
| Prototype 2 | `asc::std::uint32_t` | Returns the result of reducing the participating threads or the contiguous range according to the interface name. |
| Prototype 3 | `float` | Returns the result of reducing the participating threads or the contiguous range according to the interface name. |

## Constraints

- The input/output are UB ranges managed by the caller; all intermediate and final values of a signed sum or scan must be representable.

- Can only be called in AI Core SIMD programming.
- Parameter types, address spaces, value ranges, and object lifetimes must satisfy the declarations on this page.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/collectives>

__aicore__ unsigned int example(__ubuf__ const unsigned int* input)
{
    // The input points to at least four valid elements in the current thread block's UB.
    return asc::ub_reduce_add(asc::ub_span<const unsigned int>(input, 4u));
}
```

## Related APIs

- [API list for this header](asc_collectives.md)
