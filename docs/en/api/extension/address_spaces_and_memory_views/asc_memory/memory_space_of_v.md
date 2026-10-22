# asc::memory_space_of_v

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

`asc::memory_space_of_v<T>` is a variable template shorthand for `memory_space_of<T>::value`.

## Declaration

```cpp
namespace asc {
template<class T> inline constexpr asc::memory_space memory_space_of_v = asc::memory_space_of<T>::value;
} // namespace asc
```

## Constraints

- Provides non-owning address space views, an explicit arena, and temporary storage.

## Example

The following snippet reads the interface value with concrete template arguments.

```cpp
#include <asc/memory>

inline constexpr auto example = asc::memory_space_of_v<asc::gm_span<int>>;
```

## Related APIs

- [API list for this header](asc_memory.md)
