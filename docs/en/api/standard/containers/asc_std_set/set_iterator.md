# asc::std::set::iterator

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

Header: `<asc/std/set>`.

An `asc::std::set::iterator` can be incremented to traverse the container. Iterators obtained from `begin()`, `find()` and the result of `insert()` provide read-only access to the key. `*it` returns `const Key&` and `it.operator->()` returns `const Key*`.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `set`](https://en.cppreference.com/w/cpp/header/set).

## Declaration

Member of: [`asc::std::set`](set.md).

```cpp
// Excerpt of the declaration inside class asc::std::set; template parameters and other members are provided by the owning class.
using iterator = typename tree_type::iterator;
```

## Constraints

- In Host and AI Core SIMT programming, set<Key,Compare,A> uses an explicit GM arena.
- Construction from an allocator and from Compare+allocator.
- empty/size/begin/end/insert/find/count/clear.
- AVL balancing with a logarithmic-time insertion/lookup core.
- Duplicate-key rejection, ordered iteration, move, and destruction.
- Only the domain where capacity is sufficient and keys/comparators/allocators do not throw.
- Host and AI Core SIMT programming.

## Example

The following Host snippet explicitly provides an allocator with rebinding capability; on the device side, an allocator callable at the target execution location must be used instead.

```cpp
#include <asc/std/set>
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
    template <class U>
    struct rebind {
        using other = example_allocator<U>;
    };
    example_allocator() = default;
    template <class U>
    example_allocator(const example_allocator<U>&) noexcept
    {}
};
#include <type_traits>
#include <cstddef>
#include <utility>

using alias_type = typename asc::std::set<int, ::std::less<int>, example_allocator<int>>::iterator;
static_assert(::std::is_same_v<alias_type,
    decltype(::std::declval<asc::std::set<int, ::std::less<int>, example_allocator<int>>&>().begin())>);
```

## Related APIs

- [`asc::std::set`](set.md)
- [API list for this header](asc_std_set.md)
