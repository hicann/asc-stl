# asc::std::scoped_allocator_adaptor::select_on_container_copy_construction

## Product Support

<!-- npu="950" id1 -->
- Ascend 950PR&950DT series products: This page is a compatibility note; the described interface is not provided
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

This page keeps the original entry for compatibility notes. The adaptor itself has no `select_on_container_copy_construction()` member; nor does it recursively select inner allocators. An outer member of the same name may be visible through inheritance, but it must not be treated on that basis as a member returning a complete adaptor.

An ordinary copy can directly copy the adaptor object; if the outer allocator's copy selection is needed, use `allocator_traits` explicitly on the outer type and handle the inner allocators yourself.

## Function Prototype

The current product does not declare the interface named in this page's title. Use the provided interface described below.

## Parameters

This page declares no callable interface parameters.

## Return Value

This page declares no interface return value; see the Example section for the result of the alternative call.

## Constraints

- The adaptor itself has no `select_on_container_copy_construction()` member; nor does it recursively select inner allocators. An outer member of the same name may be visible through inheritance, but it must not be treated on that basis as a member returning a complete adaptor.
- An ordinary copy can directly copy the adaptor object; if the outer allocator's copy selection is needed, use `allocator_traits` explicitly on the outer type and handle the inner allocators yourself.

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
    const adaptor source(example_allocator<int>{7});
    const adaptor copied(source);
    return copied.outer_allocator().identity == 7;
}
```

## Related APIs

- [`asc::std::scoped_allocator_adaptor`](scoped_allocator_adaptor.md)
- [API list for this header](asc_std_scoped_allocator.md)
