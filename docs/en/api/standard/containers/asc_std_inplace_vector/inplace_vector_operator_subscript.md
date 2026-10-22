# asc::std::inplace_vector::`operator[]`

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

Header: `<asc/std/inplace_vector>`.

`asc::std::inplace_vector::operator[]` accesses the specified element when the caller guarantees the index is valid.

This interface supports both Host and the device side, both limited to the non-throwing operations listed on this page.

Standard semantics reference: [cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector).

## Function Prototype

Member of: [`inplace_vector<T, Capacity>`](inplace_vector.md). The following is the in-class declaration; type aliases and template parameters are provided by the owning class.

### Prototype 1

```cpp
constexpr reference operator[](size_type index) noexcept;
```

### Prototype 2

```cpp
constexpr const_reference operator[](size_type index) const noexcept;
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `index` | Input | The zero-based element position; it must be less than size(). |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `reference` | A writable element reference borrowing the position index; no bounds check is performed. |
| Prototype 2 | `const_reference` | A read-only element reference borrowing the position index; no bounds check is performed. |

## Constraints

- index must be less than size(), and no bounds check is performed; the returned reference is valid only while the corresponding element is alive.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/inplace_vector>

bool example()
{
    asc::std::inplace_vector<int, 4> values;
    if (!values.try_push_back(2) || !values.try_push_back(3)) return false;
    values[1] = 7;
    return values[0] == 2 && values[1] == 7;
}
```

## Related APIs

- [`asc::std::inplace_vector`](inplace_vector.md)
- [API list for this header](asc_std_inplace_vector.md)
