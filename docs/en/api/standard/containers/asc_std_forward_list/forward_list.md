# asc::std::forward_list

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

Header: `<asc/std/forward_list>`.

`asc::std::forward_list` stores elements sequentially as a singly linked list.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `forward_list`](https://en.cppreference.com/w/cpp/header/forward_list).

## Declaration

```cpp
namespace asc::std {
template<class T, class Allocator> class forward_list;
} // namespace asc::std
```

## Constraints

- In Host and AI Core SIMT programming, forward_list<T,A> is constructed with an explicit GM arena allocator.
- empty/front/begin/end.
- push_front/emplace_front/pop_front/clear.
- Move construction/assignment, where iterators obtained before the move continue traversing the target's nodes, and destruction.
- Only the domains where capacity is sufficient and values/allocators do not throw.
- Host and AI Core SIMT programming.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <memory>
#include <asc/std/forward_list>

template<class T>
struct ExampleAllocator : ::std::allocator<T> {
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template<class U> struct rebind { using other = ExampleAllocator<U>; };
    ExampleAllocator() = default;
    template<class U> ExampleAllocator(const ExampleAllocator<U>&) noexcept {}
};

bool example()
{
    asc::std::forward_list<int, ExampleAllocator<int>> values(ExampleAllocator<int>{});
    values.push_front(2);
    values.push_front(1);
    auto second = values.begin();
    ++second;
    return values.front() == 1 && *second == 2;
}
```

## Related APIs

- [API list for this header](asc_std_forward_list.md)
