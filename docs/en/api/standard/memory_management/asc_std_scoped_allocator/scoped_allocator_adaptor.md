# asc::std::scoped_allocator_adaptor

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

`asc::std::scoped_allocator_adaptor` holds an outer allocator and optional inner allocators, and delegates storage allocation and release to the outer allocator. The current `construct` constructs the object directly with the passed arguments and does not perform the standard uses-allocator recursive argument injection.

## Declaration

The primary template is listed first, followed by the two partial specializations without and with inner allocators.

```cpp
namespace asc::std {
template<class OuterAllocator, class... InnerAllocators>
class scoped_allocator_adaptor;

template<class OuterAllocator>
class scoped_allocator_adaptor<OuterAllocator>;

template<class OuterAllocator, class FirstInner, class... RestInner>
class scoped_allocator_adaptor<OuterAllocator, FirstInner, RestInner...>;
}
```

## Constraints

- `OuterAllocator` must itself provide `value_type`, `pointer`, `size_type`, `difference_type`, and the members needed for rebinding; this class does not fill in these names with `allocator_traits`.
- `allocate`, `deallocate`, and `max_size` directly use the outer allocator's corresponding operations. The inner allocators can be queried through `inner_allocator()`.
- `construct` only forwards the arguments given by the caller; it does not automatically pass `allocator_arg` or inner allocators, and does not recursively process pairs.
- The full standard propagation traits, recursive copy selection, and hint-allocation overloads are not provided. Members of the same name inherited from the outer allocator carry only the semantics of that outer type itself.
- Device-side use requires the allocators and element operations to be valid and non-throwing at the corresponding execution location.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/memory>
#include <asc/std/scoped_allocator>
#include <memory>
#include <limits>

template<class T>
struct example_allocator {
    using value_type = T;
    using pointer = T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    template<class U> struct rebind { using other = example_allocator<U>; };
    int identity = 0;
    T* allocate(size_type count) { return std::allocator<T>{}.allocate(count); }
    void deallocate(T* address, size_type count) { std::allocator<T>{}.deallocate(address, count); }
    size_type max_size() const noexcept { return std::numeric_limits<size_type>::max() / sizeof(T); }
};

bool example()
{
    using adaptor = asc::std::scoped_allocator_adaptor<example_allocator<int>>;
    adaptor allocator(example_allocator<int>{7});
    int* pointer = allocator.allocate(1);
    allocator.construct(pointer, 9);
    const bool valid = allocator.outer_allocator().identity == 7 && *pointer == 9;
    allocator.destroy(pointer);
    allocator.deallocate(pointer, 1);
    return valid;
}
```

## Related APIs

- [API list for this header](asc_std_scoped_allocator.md)
