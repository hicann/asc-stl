# asc::std::allocator_traits::difference_type

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

`asc::std::allocator_traits::difference_type` identifies the signed type for iterator distances.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Declaration

`asc::std::allocator_traits<Allocator>::difference_type` is a member type alias.

If Allocator provides difference_type, that type is used; otherwise pointer_traits<pointer>::difference_type is used.

In a dependent-type context, use the following form:

```cpp
template<class Allocator>
using selected_difference_type = typename asc::std::allocator_traits<Allocator>::difference_type;
```

## Constraints

- If Allocator provides difference_type, that type is used; otherwise pointer_traits<pointer>::difference_type is used.
- `Allocator` is the allocator type explicitly provided by the caller; this member type query performs no allocation.

## Example

The following Host snippet explicitly provides an allocator with rebind capability; on the device side, an allocator callable at the target execution location must be used instead.

```cpp
#include <asc/std/memory>
#include <asc/std/type_traits>
#include <memory>

template <class T>
struct example_allocator : ::std::allocator<T> {
    using value_type = T;
    using pointer = T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template <class U> struct rebind { using other = example_allocator<U>; };
    example_allocator() = default;
    template <class U> example_allocator(const example_allocator<U>&) noexcept {}
};

using selected = typename asc::std::allocator_traits<example_allocator<int>>::difference_type;

static_assert(asc::std::is_same_v<selected, ::std::ptrdiff_t>);
```

## Related APIs

- [API list for this header](asc_std_memory.md)
