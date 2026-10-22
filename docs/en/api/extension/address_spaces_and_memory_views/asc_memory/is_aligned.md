# asc::is_aligned

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

Header: `<asc/memory>`.

`asc::is_aligned` checks whether an integer address value or a pointer satisfies a given byte-alignment requirement.

## Function Prototype

### Prototype 1

```cpp
namespace asc {
template<class Integer> constexpr bool is_aligned(Integer value, Integer alignment) noexcept;
} // namespace asc
```

### Prototype 2

```cpp
namespace asc {
template<class T> constexpr bool is_aligned(T* pointer, asc::std::size_t alignment) noexcept;
} // namespace asc
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Integer` | Integer type shared by the address value and the alignment value; must support the modulo operation. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Integer address value to check; considered aligned when value modulo alignment is 0 (and alignment is non-zero). |
| `alignment` | Input | Multiple to check against; 0 returns false. The pointer form uses bytes as the unit, and the integer form uses the same unit as value. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Type of the object the pointer points to; used only to deduce the pointer parameter—this interface does not dereference the pointer. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pointer` | Input | Pointer to check; only its address value is used for the byte-alignment check against alignment, and the pointed-to object is not accessed. |
| `alignment` | Input | Multiple to check against; 0 returns false. The pointer form uses bytes as the unit, and the integer form uses the same unit as value. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `bool` | `true` when alignment is non-zero and the value / address is divisible by alignment. |
| Prototype 2 | `bool` | `true` when alignment is non-zero and the value / address is divisible by alignment. |

## Constraints

- `alignment == 0` explicitly returns `false`; a positive `alignment` is not required to be a power of two; actually allocating or accessing an object must still satisfy the alignment requirements of the corresponding interface.
- The integer overload requires value and alignment to support the modulo operation.
- The pointer overload checks byte alignment by address value.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/memory>

bool example()
{
    return asc::is_aligned(14, 7) && !asc::is_aligned(15, 7) && !asc::is_aligned(14, 0);
}
```

## Related APIs

- [API list for this header](asc_memory.md)
