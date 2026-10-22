# asc::std::list::`operator=`

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

`asc::std::list::operator=` updates the object with the selected assignment overload and returns the specified result.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `list`](https://en.cppreference.com/w/cpp/header/list).

## Function Prototype

Member of: [`asc::std::list`](list.md).

```cpp
// Excerpt of the declaration inside class asc::std::list; template parameters and other members are provided by the owning class.
list<T, Allocator>& operator=(list<T, Allocator>&& other) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | The object assigned from; the lvalue form copies its state, and the rvalue form transfers the state through the move operations of the corresponding members. |

## Return Value

| Return type | Description |
| --- | --- |
| `list<T, Allocator> &` | Returns a reference to the updated current object, which can continue to be used in assignment or compound operations. |

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

void example(asc::std::list<int, example_allocator<int>>& target, asc::std::list<int, example_allocator<int>>& source)
{
    target = static_cast<asc::std::list<int, example_allocator<int>>&&>(source);
}
```

## Related APIs

- [`asc::std::list`](list.md)
- [API list for this header](asc_std_list.md)
