# asc::work_chunk

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

Header: `<asc/work_queue>`.

`asc::work_chunk<Index>` represents the half-open work range `[begin, end)` obtained by one successful acquisition, and can query whether the range is empty and how many indices it contains.

This interface is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

## Declaration

```cpp
namespace asc {
template <class Index>
class work_chunk;
}  // namespace asc
```

## Constraints

- Index supports uint32_t, uint64_t, and 64-bit unsigned long long; other types are not automatically accepted just because their width matches. The Host can perform value operations and acquisition, device participants must still use a shared GM cursor, and SIMD uses the corresponding GM-qualified entry.

- Index must be a supported 32-bit or 64-bit unsigned integer.
- The range is interpreted as [begin, end); when begin is not less than end, empty is true and size is 0.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/work_queue>
#include <asc/std/cstdint>

bool example()
{
    asc::work_chunk<asc::std::uint32_t> chunk(2U, 5U);
    return chunk.begin == 2 && chunk.end == 5 && chunk.size() == 3 && !chunk.empty();
}
```

## Related APIs

- [API list for this header](asc_work_queue.md)
