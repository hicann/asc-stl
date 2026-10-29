# asc::std::deque::~deque

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

Header: `<asc/std/deque>`.

`asc::std::deque::~deque` destroys the `deque` object and ends its lifetime.

Standard semantics reference: [cppreference `deque`](https://en.cppreference.com/w/cpp/header/deque).

## Function Prototype

```cpp
~deque();
```

## Parameters

No parameters.

## Return Value

No return value.

## Constraints

- Explicit-allocator construction of deque<T,A>.
- push/emplace/pop_front/back within a bounded block map.
- empty/size/front/back/`operator[]` and the random-access iteration core.
- References to existing elements remain stable when a new end block is allocated.
- clear/destruction.
- Only the domains where capacity is sufficient and exceptions are not thrown.

## Example

The following snippet assumes that object points to a constructed object; after explicit destruction the object must not be accessed again, and the caller is responsible for releasing the storage.

```cpp
#include <asc/std/deque>
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
    using sequence = asc::std::deque<int, counted_allocator<int>>;
    alignas(sequence) unsigned char storage[sizeof(sequence)];
    auto* values = ::new (static_cast<void*>(storage)) sequence(counted_allocator<int>(counts));
    values->push_back(7);
    const bool constructed = !values->empty() && values->front() == 7 && counts.allocated > 0;
    values->~sequence();
    return constructed && counts.allocated == counts.released;
}
```

## Related APIs

- [API list for this header](asc_std_deque.md)
