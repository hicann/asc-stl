# asc::std::aligned_storage::type

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

`asc::std::aligned_storage::type` holds the raw storage type that satisfies the specified size and alignment.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

Member of: [`asc::std::aligned_storage`](aligned_storage.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside asc::std::aligned_storage; template parameters and other members are provided by the owning class.
struct type;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside asc::std::aligned_storage; template parameters and other members are provided by the owning class.
union type;
```

## Constraints

- The result provides a raw storage type of at least `Len` bytes that satisfies the specified `Align`; the lifetime of any object stored in it must be started and ended by the caller according to the rules for that object.

## Example

The following Host example checks the interface result against an independent expected type or value.

```cpp
#include <asc/std/type_traits>

using storage_type = typename asc::std::aligned_storage<sizeof(double), alignof(double)>::type;
static_assert(sizeof(storage_type) >= sizeof(double));
static_assert(alignof(storage_type) >= alignof(double));
```

## Related APIs

- [`asc::std::aligned_storage`](aligned_storage.md)
- [API list for this header](asc_std_type_traits.md)
