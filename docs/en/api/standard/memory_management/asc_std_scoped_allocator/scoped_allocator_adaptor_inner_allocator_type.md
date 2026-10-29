# asc::std::scoped_allocator_adaptor::inner_allocator_type

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

Header: `<asc/std/scoped_allocator>`.

`asc::std::scoped_allocator_adaptor::inner_allocator_type` identifies the inner allocator type recursively passed to elements.

Standard semantics reference: [cppreference `scoped_allocator`](https://en.cppreference.com/w/cpp/header/scoped_allocator).

## Declaration

Member of: [`asc::std::scoped_allocator_adaptor`](scoped_allocator_adaptor.md).

### Prototype 1

```cpp
// Declaration excerpt from inside the asc::std::scoped_allocator_adaptor class; template parameters and other members are provided by the enclosing class.
using inner_allocator_type = scoped_allocator_adaptor<FirstInner, RestInner...>;
```

### Prototype 2

```cpp
// Declaration excerpt from inside the asc::std::scoped_allocator_adaptor class; template parameters and other members are provided by the enclosing class.
using inner_allocator_type = scoped_allocator_adaptor<OuterAllocator>;
```

## Constraints

- This type is determined directly by the outer or the stored inner allocator; the nonexistent `outer_traits` alias is not used to fill in the type.
- The type query accesses no elements and changes no allocator state; see the adaptor and the corresponding member pages for the actual operation requirements.

## Example

The following Host snippet explicitly provides an allocator with rebind capability; on the device side, an allocator callable at the target execution location must be used instead.

```cpp
#include <asc/std/scoped_allocator>
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

using selected = typename asc::std::scoped_allocator_adaptor<example_allocator<int>>::inner_allocator_type;

static_assert(asc::std::is_same_v<selected, asc::std::scoped_allocator_adaptor<example_allocator<int>>>);
```

## Related APIs

- [`asc::std::scoped_allocator_adaptor`](scoped_allocator_adaptor.md)
- [API list for this header](asc_std_scoped_allocator.md)
