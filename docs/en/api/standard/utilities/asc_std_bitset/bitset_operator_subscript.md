# asc::std::bitset::`operator[]`

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

Header: `<asc/std/bitset>`.

`asc::std::bitset::operator[]` accesses the specified element when the caller guarantees the index is valid.

Standard semantics reference: [cppreference `bitset`](https://en.cppreference.com/w/cpp/header/bitset).

## Function Prototype

Member of: [`asc::std::bitset`](bitset.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside class asc::std::bitset; template parameters and other members are provided by the owning class.
constexpr const_reference operator[](size_t position) const;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside class asc::std::bitset; template parameters and other members are provided by the owning class.
constexpr reference operator[](size_t position);
```


## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `position` | Input | The index of the element to access; the caller must guarantee the index is within the valid range. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `position` | Input | The index of the element to access; the caller must guarantee the index is within the valid range. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `const_reference` | Returns the element reference or proxy value at the specified index; the index must be valid. |
| Prototype 2 | `reference` | Returns the element reference or proxy value at the specified index; the index must be valid. |

## Constraints

- The number of bits `Size` of the owning bitset is fixed at compile time; the operation performs no dynamic allocation. The subscript must be less than `Size`; no bounds checking is performed, and the proxy reference depends on the storage of the original bitset.

## Example

The following Host snippet demonstrates a concrete call with an 8-bit bitset; indices must be within the valid range.

```cpp
#include <asc/std/bitset>

decltype(auto) example(const asc::std::bitset<8>& bits)
{
    return bits[0];
}

bool verify_example()
{
    const asc::std::bitset<8> bits(3u);
    return example(bits);
}
```

## Related APIs

- [`asc::std::bitset`](bitset.md)
- [API list for this header](asc_std_bitset.md)
