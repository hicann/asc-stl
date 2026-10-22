# asc::std::forward_list::~forward_list

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

`asc::std::forward_list::~forward_list` destroys the `forward_list` object and ends its lifetime.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `forward_list`](https://en.cppreference.com/w/cpp/header/forward_list).

## Function Prototype

```cpp
~forward_list();
```

## Parameters

No parameters.

## Return Value

No return value.

## Constraints

- In Host and AI Core SIMT programming, forward_list<T,A> is constructed with an explicit GM arena allocator.
- empty/front/begin/end.
- push_front/emplace_front/pop_front/clear.
- Move construction/assignment, where iterators obtained before the move continue traversing the target's nodes, and destruction.
- Only the domains where capacity is sufficient and values/allocators do not throw.
- Host and AI Core SIMT programming.

## Example

The following snippet assumes that object points to a constructed object; after explicit destruction the object must not be accessed again, and the caller is responsible for releasing the storage.

```cpp
#include <asc/std/forward_list>
#include <functional>
#include <memory>
#include <string>
#include <utility>

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

using example_object = asc::std::forward_list<int, example_allocator<int>>;
void example(example_object* object)
{
    // object points to a constructed object; after destruction the object must not be accessed again.
    object->~example_object();
}
```

## Related APIs

- [API list for this header](asc_std_forward_list.md)
