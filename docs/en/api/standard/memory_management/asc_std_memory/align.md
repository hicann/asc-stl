# asc::std::align

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

`asc::std::align` finds a position in caller-provided storage that satisfies the size and alignment requirements.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Function Prototype

```cpp
namespace asc::std {
void* align(size_t alignment, size_t size, void*& pointer, size_t& space) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `alignment` | Input | The byte alignment value; must be a non-negative integer power of two, for example 1, 2, 4, or 8. |
| `size` | Input | The number of contiguous bytes required at the aligned address. |
| `pointer` | Input/Output | On input, the start of the available buffer; on success it is advanced to the address satisfying alignment while space is correspondingly reduced, and on failure both are left unchanged. |
| `space` | Input/Output | On input, the number of contiguous bytes available starting at `pointer`; on success only the padding bytes consumed to align the start are deducted, not `size`. |

## Return Value

| Return type | Description |
| --- | --- |
| `void *` | Returns the storage address satisfying the required alignment; returns a null pointer when the space is insufficient. |

## Constraints

- The caller must provide valid contiguous storage of at least `space` bytes starting at `pointer`; this interface allocates no memory and constructs no objects.
- Returns `nullptr` and leaves `pointer` and `space` unchanged when `alignment` is invalid, `pointer` is null, rounding the address overflows, or the remaining space is insufficient.
- On success, returns the aligned address and updates `pointer`; `space` is reduced only by the alignment padding bytes.

## Example

The following Host example uses a concrete object and checks the result of the call.

```cpp
#include <asc/std/memory>
#include <asc/std/cstddef>

bool example()
{
    alignas(16) unsigned char storage[32]{};
    void* pointer = storage + 1;
    asc::std::size_t space = 31;
    void* result = asc::std::align(16, 8, pointer, space);
    if (result != storage + 16 || pointer != result || space != 16) return false;
    // Alignment is already satisfied, but 17 bytes do not fit in the remaining space; failure does not modify the input/output parameters.
    return asc::std::align(16, 17, pointer, space) == nullptr &&
        pointer == result && space == 16;
}
```

## Related APIs

- [API list for this header](asc_std_memory.md)
