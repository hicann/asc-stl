# asc::std::aligned_alloc

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

Header: `<asc/std/cstdlib>`.

`asc::std::aligned_alloc` is provided by `<asc/std/cstdlib>`; it allocates memory by byte count and alignment value, and returns a null pointer when the alignment is not legal.

Standard semantics reference: [cppreference `cstdlib`](https://en.cppreference.com/w/cpp/header/cstdlib).

## Function Prototype

```cpp
namespace asc::std {
[[nodiscard]] void* aligned_alloc(size_t nbytes, size_t alignment) noexcept;
}
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `nbytes` | Input | The number of bytes to allocate; must be an integer multiple of `alignment`. |
| `alignment` | Input | The alignment value in bytes; must be a non-negative integer power of 2, and is limited by the range supported by the Host C library. |

## Return Value

| Return type | Description |
| --- | --- |
| `void*` | Returns the allocated address satisfying the alignment requirement on success, and nullptr on failure; it must be released via ::std::free. |

## Constraints

- For Host use only; the parameter order is byte count first, alignment second.
- `alignment` must be a non-negative integer power of 2, and `nbytes` must be an integer multiple of `alignment`; `nullptr` is returned when these are not satisfied.
- The alignment requirements supported by the Host C library must also be satisfied; a successful allocation must be released by calling ::std::free.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/cstdlib>
#include <asc/std/cstdint>
#include <cstdlib>

bool example()
{
    void* pointer = asc::std::aligned_alloc(64, 32);
    if (pointer == nullptr) return false;
    const bool aligned = reinterpret_cast<asc::std::uintptr_t>(pointer) % 32 == 0;
    ::std::free(pointer);
    return aligned;
}
```

## Related APIs

- [API list for this header](asc_std_cstdlib.md)
