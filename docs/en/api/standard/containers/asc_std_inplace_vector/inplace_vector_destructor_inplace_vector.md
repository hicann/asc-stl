# asc::std::inplace_vector::~inplace_vector

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

Header: `<asc/std/inplace_vector>`.

`asc::std::inplace_vector::~inplace_vector` destroys the `inplace_vector` object and ends its lifetime.

This interface supports both Host and the device side, both limited to the non-throwing operations listed on this page.

Standard semantics reference: [cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector).

## Function Prototype

```cpp
~inplace_vector();
```

## Parameters

No parameters.

## Return Value

No return value.

## Constraints

- Destroys the currently constructed elements; after the object is destroyed, all of its references, pointers, and iterators become unusable.
- The corresponding construction, assignment, and destruction of elements must satisfy the non-throwing usage domain; the constexpr declaration does not guarantee constant evaluation for every T and language mode.

## Example

The following snippet assumes that object points to a constructed object; after explicit destruction the object must not be accessed again, and releasing the storage is the caller's responsibility.

```cpp
#include <asc/std/inplace_vector>
#include <new>

struct counted_value {
    int* live;
    explicit counted_value(int& count) : live(&count)
    {
        ++*live;
    }
    counted_value(counted_value&& other) : live(other.live)
    {
        ++*live;
    }
    ~counted_value()
    {
        --*live;
    }
};

bool example()
{
    int live = 0;
    using sequence = asc::std::inplace_vector<counted_value, 2>;
    alignas(sequence) unsigned char storage[sizeof(sequence)];
    auto* values = ::new (static_cast<void*>(storage)) sequence;
    const auto added = values->try_emplace_back(live);
    const bool constructed = added.has_value() && live == 1;
    values->~sequence();
    return constructed && live == 0;
}
```

## Related APIs

- [API list for this header](asc_std_inplace_vector.md)
