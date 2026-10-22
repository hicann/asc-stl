# asc::std::unordered_map::value_type

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

Header: `<asc/std/unordered_map>`.

`asc::std::unordered_map::value_type` designates the value type of elements or results.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `unordered_map`](https://en.cppreference.com/w/cpp/header/unordered_map).

## Declaration

value_type is the key-value entry type exposed by the container. The following shows the public type query; entry_type is just an example alias.

```cpp
template<class Key, class T, class Hash, class Equal, class Allocator>
using entry_type =
    typename asc::std::unordered_map<Key, T, Hash, Equal, Allocator>::value_type;
```

## Constraints

- Entries have `const Key first` and `T second` members.
- Entries should be constructed with the container's value_type; it must not be assumed to be the same type as asc::std::pair<const Key, T>.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/unordered_map>
#include <asc/std/type_traits>
#include <functional>
#include <memory>
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

using entry_type = typename asc::std::unordered_map<int, int, ::std::hash<int>, ::std::equal_to<int>, example_allocator<::std::pair<const int, int>>>::value_type;
static_assert(asc::std::is_same_v<decltype(::std::declval<entry_type>().first), const int>);
static_assert(asc::std::is_same_v<decltype(::std::declval<entry_type>().second), int>);

bool example()
{
    const entry_type entry(7, 9);
    return entry.first == 7 && entry.second == 9;
}
```

## Related APIs

- [`asc::std::unordered_map`](unordered_map.md)
- [API list for this header](asc_std_unordered_map.md)
