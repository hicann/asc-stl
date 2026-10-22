# asc::std::list::iterator

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

Header: `<asc/std/list>`.

`asc::std::list::iterator` is the iterator type for traversing the elements of the corresponding container.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `list`](https://en.cppreference.com/w/cpp/header/list).

## Declaration

Member of: [`asc::std::list`](list.md).

```cpp
// Excerpt of the declaration inside class asc::std::list; template parameters and other members are provided by the owning class.
class iterator;
```

## Constraints

- In Host and AI Core SIMT programming, list<T,A> is constructed with an explicit GM arena allocator.
- empty/size/front/back/begin/end.
- push/emplace/pop_front/back/clear.
- Bidirectional iteration core, move construction/assignment, where iterators obtained before the move continue traversing the target's nodes, and destruction.
- Only the domains where capacity is sufficient and values/allocators do not throw.
- Host and AI Core SIMT programming.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <memory>
#include <asc/std/list>

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
    using Container = asc::std::list<int, ExampleAllocator<int>>;
    Container values(ExampleAllocator<int>{});
    values.push_back(2);
    values.push_back(4);
    auto it = values.begin();
    *it = 7;
    return values.front() == 7 && *++it == 4;
}
```

## Related APIs

- [`asc::std::list`](list.md)
- [API list for this header](asc_std_list.md)
