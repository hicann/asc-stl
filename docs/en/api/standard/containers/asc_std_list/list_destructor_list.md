# asc::std::list::~list

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

`asc::std::list::~list` destroys the `list` object and ends its lifetime.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `list`](https://en.cppreference.com/w/cpp/header/list).

## Function Prototype

```cpp
~list();
```

## Parameters

No parameters.

## Return Value

No return value.

## Constraints

- In Host and AI Core SIMT programming, list<T,A> is constructed with an explicit GM arena allocator.
- empty/size/front/back/begin/end.
- push/emplace/pop_front/back/clear.
- Bidirectional iteration core, move construction/assignment, where iterators obtained before the move continue traversing the target's nodes, and destruction.
- Only the domains where capacity is sufficient and values/allocators do not throw.
- Host and AI Core SIMT programming.

## Example

The following snippet assumes that object points to a constructed object; after explicit destruction the object must not be accessed again, and the caller is responsible for releasing the storage.

```cpp
#include <asc/std/list>
#include <memory>
#include <new>

struct allocation_counts {
    int allocated = 0;
    int released = 0;
};

template <class T>
struct counted_allocator {
    using value_type = T;
    using pointer = T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template <class U>
    struct rebind {
        using other = counted_allocator<U>;
    };
    allocation_counts* counts;
    explicit counted_allocator(allocation_counts& value) : counts(&value)
    {}
    template <class U>
    counted_allocator(const counted_allocator<U>& other) : counts(other.counts)
    {}
    T* allocate(::std::size_t count)
    {
        T* result = ::std::allocator<T>{}.allocate(count);
        ++counts->allocated;
        return result;
    }
    void deallocate(T* pointer, ::std::size_t count)
    {
        ::std::allocator<T>{}.deallocate(pointer, count);
        ++counts->released;
    }
};

bool example()
{
    allocation_counts counts;
    using sequence = asc::std::list<int, counted_allocator<int>>;
    alignas(sequence) unsigned char storage[sizeof(sequence)];
    auto* values = ::new (static_cast<void*>(storage)) sequence(counted_allocator<int>(counts));
    values->push_back(7);
    const bool constructed = !values->empty() && values->front() == 7 && counts.allocated > 0;
    values->~sequence();
    return constructed && counts.allocated == counts.released;
}
```

## Related APIs

- [API list for this header](asc_std_list.md)
