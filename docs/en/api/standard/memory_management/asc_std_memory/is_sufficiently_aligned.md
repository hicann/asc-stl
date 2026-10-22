# asc::std::is_sufficiently_aligned

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

Header: `<asc/std/memory>`.

`asc::std::is_sufficiently_aligned` determines whether a pointer satisfies the specified compile-time alignment requirement.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Function Prototype

```cpp
namespace asc::std {
template<size_t ByteAlignment, class ElementType> [[nodiscard]] bool is_sufficiently_aligned(ElementType* pointer) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ByteAlignment` | The required byte alignment; must satisfy the compile-time validity conditions below. |
| `ElementType` | The element type accessed by the view, which determines the types of reads, transformations, and returned values. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pointer` | Input | Only checks whether the address satisfies the byte alignment specified by ByteAlignment; does not read the pointed-to object and does not adjust the address. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, otherwise `false`. |

## Constraints

- This overload accepts only raw object pointers `ElementType*`, not fancy pointer objects.
- `ByteAlignment` must be a non-negative integer power of two; when the element type is not void, it must also be no less than `alignof(ElementType)`.
- Only checks whether the address value satisfies the specified byte alignment; does not read the object and does not guarantee sufficient storage at the address or the existence of a live object.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/memory>

bool example()
{
    alignas(16) int values[4] = {1, 2, 3, 4};
    return asc::std::is_sufficiently_aligned<16>(values)
        && !asc::std::is_sufficiently_aligned<16>(values + 1);
}
```

## Related APIs

- [API list for this header](asc_std_memory.md)
