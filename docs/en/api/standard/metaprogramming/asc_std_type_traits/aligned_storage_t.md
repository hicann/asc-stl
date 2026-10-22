# asc::std::aligned_storage_t

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

Header: `<asc/std/type_traits>`.

`asc::std::aligned_storage_t` computes a raw storage type that satisfies the specified size and alignment, providing the result as a type alias.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

Declaration summary. The default `Align` uses an implementation-chosen alignment value, which can be queried through `alignof(typename aligned_storage<Len>::type)`.

```cpp
namespace asc::std {
template<size_t Len, size_t Align = alignof(typename aligned_storage<Len>::type)>
using aligned_storage_t = typename aligned_storage<Len, Align>::type;
} // namespace asc::std
```

## Constraints

- This helper form uses the same type preconditions and decision rules as [`asc::std::aligned_storage`](aligned_storage.md); the result corresponds to the `type` of the trait class.

## Example

The following Host example checks the interface result against an independent expected type or value.

```cpp
#include <asc/std/type_traits>

using storage_type = asc::std::aligned_storage_t<sizeof(double), alignof(double)>;
static_assert(sizeof(storage_type) >= sizeof(double));
static_assert(alignof(storage_type) >= alignof(double));
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
