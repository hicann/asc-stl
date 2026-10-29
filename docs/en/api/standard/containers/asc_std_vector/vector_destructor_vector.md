# asc::std::vector::~vector

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

Header: `<asc/std/vector>`.

`asc::std::vector::~vector` destroys the `vector` object and ends its lifetime.

Standard semantics reference: [cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector).

## Function Prototype

```cpp
~vector();
```

## Parameters

No parameters.

## Return Value

No return value.

## Constraints

- The destructor destroys all live elements and then frees the storage with the saved allocator; element destruction and allocator deallocation must not throw.
- After destruction completes, pointers, references, and iterators to the original elements are invalidated.
- When destroying on the device side, element destruction and allocator deallocation must be available in the corresponding programming mode.

## Example

The following snippet focuses on calling this interface; inputs, resources, and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/vector>
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
    using sequence = asc::std::vector<int, counted_allocator<int>>;
    alignas(sequence) unsigned char storage[sizeof(sequence)];
    auto* values = ::new (static_cast<void*>(storage)) sequence(counted_allocator<int>(counts));
    values->push_back(7);
    const bool constructed = !values->empty() && values->front() == 7 && counts.allocated > 0;
    values->~sequence();
    return constructed && counts.allocated == counts.released;
}
```

The corresponding complete project uses `C++17` and has been verified by Host compilation and execution.

Complete example source: [explicit_allocator_vector.cpp](../../../../../zh/examples/explicit_allocator_vector.cpp).

## Related APIs

- [API list for this header](asc_std_vector.md)
