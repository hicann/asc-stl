# asc::memory_space_of

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

`asc::memory_space_of<T>` is a customizable type trait that obtains the `memory_space` corresponding to a supported memory view type; `gm_span` and `ub_span` map to GM and UB respectively.

## Declaration

```cpp
namespace asc {
template<class T> struct memory_space_of;
} // namespace asc
```

## Constraints

- Provides non-owning address space views, an explicit arena, and temporary storage.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/memory>

bool example()
{
    static_assert(asc::memory_space_of<asc::gm_span<int>>::value == asc::memory_space::global);
    return true;
}
```

## Related APIs

- [API list for this header](asc_memory.md)
