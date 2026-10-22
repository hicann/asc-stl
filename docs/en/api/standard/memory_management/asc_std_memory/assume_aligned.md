# asc::std::assume_aligned

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

`asc::std::assume_aligned` conveys pointer alignment information to the compiler when the caller guarantees the alignment precondition.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Function Prototype

```cpp
namespace asc::std {
template<size_t Align, class T> [[nodiscard]] constexpr T* assume_aligned(T* pointer) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Align` | The required byte alignment; must satisfy the compile-time validity conditions below. |
| `T` | The type of object being constructed, destroyed, or managed. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pointer` | Input | An address that must already satisfy the byte alignment specified by the template argument; the function does not adjust the address, and the behavior is undefined when the alignment requirement is not satisfied. |

## Return Value

| Return type | Description |
| --- | --- |
| `T *` | Returns the same pointer as the input address and asserts to the compiler that it satisfies the specified alignment requirement. |

## Constraints

- This overload accepts only raw object pointers `T*`, not fancy pointer objects.
- `Align` must be a non-negative integer power of two; when the element type is not void, it must also be no less than `alignof(T)`.
- The input address must already satisfy the specified byte alignment; this function expresses an alignment assumption and does not check, repair, or allocate addresses.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/memory>

bool example()
{
    alignas(16) int values[4] = {1, 2, 3, 4};
    int* pointer = asc::std::assume_aligned<16>(values);
    return pointer == values && pointer[2] == 3;
}
```

## Related APIs

- [API list for this header](asc_std_memory.md)
