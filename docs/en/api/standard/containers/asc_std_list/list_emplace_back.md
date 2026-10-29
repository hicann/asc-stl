# asc::std::list::emplace_back

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

`asc::std::list::emplace_back` constructs an element in place at the end of the container.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `list`](https://en.cppreference.com/w/cpp/header/list).

## Function Prototype

Member of: [`asc::std::list`](list.md).

```cpp
// Excerpt of the declaration inside class asc::std::list; template parameters and other members are provided by the owning class.
template<class ...Args> reference emplace_back(Args&&... args);
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Args` | The list of argument types passed to the constructor or callable object. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `args` | Input/Output | The list of arguments forwarded to the object construction or function call. |

## Return Value

| Return type | Description |
| --- | --- |
| `reference` | Returns a reference to the newly constructed element. |

## Constraints

- In Host and AI Core SIMT programming, list<T,A> is constructed with an explicit GM arena allocator.
- empty/size/front/back/begin/end.
- push/emplace/pop_front/back/clear.
- Bidirectional iteration core, move construction/assignment, where iterators obtained before the move continue traversing the target's nodes, and destruction.
- Only the domains where capacity is sufficient and values/allocators do not throw.
- Host and AI Core SIMT programming.

## Example

The following Host snippet uses an explicitly provided allocator; on the device side, an allocator callable at the target execution location must be used.

```cpp
#include <asc/std/list>
#include <memory>

template <class T>
struct example_allocator : ::std::allocator<T> {
    using value_type = T;
    using pointer = T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template <class U>
    struct rebind {
        using other = example_allocator<U>;
    };
    example_allocator() = default;
    template <class U>
    example_allocator(const example_allocator<U>&) noexcept
    {}
};

bool example()
{
    using sequence = asc::std::list<int, example_allocator<int>>;
    sequence values(example_allocator<int>{});
    values.emplace_back(7);
    values.emplace_back(9);
    return values.size() == 2 && values.front() == 7 && values.back() == 9;
}
```

## Related APIs

- [`asc::std::list`](list.md)
- [API list for this header](asc_std_list.md)
