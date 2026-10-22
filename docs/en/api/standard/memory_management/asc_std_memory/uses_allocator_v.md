# asc::std::uses_allocator_v

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

`asc::std::uses_allocator_v` determines at compile time whether a type uses a given allocator.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Declaration

```cpp
namespace asc::std {
template<class T, class Alloc>
inline constexpr bool uses_allocator_v = uses_allocator<T, Alloc>::value;
}
```

## Constraints

- An ordinary type yields `true` when it has `allocator_type` and `Alloc` is convertible to that type, otherwise `false`; `tuple` uses its public specialization rules.
- Reading this variable template constructs no objects, passes no allocator, and does not guarantee that a specific constructor is callable.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/memory>

struct example_allocator {};
struct allocated_value { using allocator_type = example_allocator; };
static_assert(asc::std::uses_allocator_v<allocated_value, example_allocator>);
static_assert(!asc::std::uses_allocator_v<int, example_allocator>);
```

## Related APIs

- [API list for this header](asc_std_memory.md)
