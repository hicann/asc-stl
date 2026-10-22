# asc::gm_span

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

`asc::gm_span<T>` is a non-owning contiguous GM memory view that stores a pointer to the first element and the element count; it can be used for access, slicing, and byte-count queries.

GM stands for Global Memory, the data space accessible from the device side; the view requires the underlying storage to be located in GM and to remain accessible while the view is in use. For an overview of the memory views and memory space interfaces provided by `<asc/memory>`, see [asc/memory header notes](asc_memory.md).

## Declaration

```cpp
namespace asc {
template<class T> class gm_span;
} // namespace asc
```

## Constraints

- In AI Core SIMD programming, element subscript access returns a reference that preserves the GM (`__gm__`) address space and the element's const qualification; on Host it is a plain reference.
- The view does not manage the storage lifetime.
- The underlying GM region must remain valid while the view is in use.
- The valid range of operator[] indices is guaranteed by the caller.
- first/last/subspan slicing uses fail-closed semantics: when the count or offset goes beyond [0, size()], an empty view is returned and no wrapped-around pointer is produced.

## Example

The following snippet demonstrates view construction, size queries, element access, and slicing; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/memory>

bool use_gm_span()
{
    // The view does not own storage: the Host snippet uses a local array as the underlying
    // storage, while the device side points to a GM region;
    // the underlying storage must remain valid while the view is in use.
    int storage[4] = {1, 2, 3, 4};
    asc::gm_span<int> view(storage, 4);

    bool ok = view.size() == 4 && !view.empty();
    ok = ok && view.size_bytes() == 4 * sizeof(int);
    ok = ok && view.data()[0] == 1 && view[1] == 2;  // data pointer and subscript access
    ok = ok && view.first(2)[1] == 2;                // slice: first 2 elements
    ok = ok && view.last(1)[0] == 4;                 // slice: last 1 element
    ok = ok && view.subspan(1, 2)[0] == 2;           // slice: 2 elements starting at offset 1
    return ok;
}
```

## Related APIs

- [API list for this header](asc_memory.md)
