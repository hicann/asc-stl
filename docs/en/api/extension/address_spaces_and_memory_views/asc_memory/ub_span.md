# asc::ub_span

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

`asc::ub_span<T>` is a non-owning contiguous UB memory view that stores a pointer to the first element and the element count; it can be used for access, slicing, and byte-count queries.

## Declaration

```cpp
namespace asc {
template <class T>
class ub_span;
}  // namespace asc
```

## Constraints

- In AI Core SIMD programming, element subscript access returns a reference that preserves the UB (`__ubuf__`) address space and the element's const qualification; on Host it is a plain reference.
- AI Core SIMD uses the real UB address space; on Host, a plain pointer representation can be constructed to describe or inspect layouts. The Host representation does not provide access to the physical device UB; AI Core SIMT programming does not provide this type.
- The view does not manage the storage lifetime.
- The underlying UB region must remain valid while the view is in use.
- The valid range of operator[] indices is guaranteed by the caller; first/last/subspan slicing uses fail-closed semantics—when the count or offset goes beyond [0, size()], an empty view is returned and no wrapped-around pointer is produced.

## Example

The following snippet is compiled for AI Core SIMD programming. The caller provides a valid UB region of at least 4 ints; this view does not allocate or free it.

```cpp
#include <asc/memory>

__aicore__ bool example(__ubuf__ int* storage)
{
    asc::ub_span<int> values(storage, 4);
    values[1] = 7;
    auto tail = values.subspan(1, 2);
    return tail.size() == 2 && tail[0] == 7;
}
```

## Related APIs

- [API list for this header](asc_memory.md)
