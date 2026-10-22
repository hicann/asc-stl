# asc::std::uses_allocator

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

Header: `<asc/std/memory>`, `<asc/std/tuple>`.

`asc::std::uses_allocator` determines at compile time whether a type accepts construction with a specified allocator.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Declaration

### Prototype 1

```cpp
namespace asc::std {
template<class T, class Allocator> struct uses_allocator;
} // namespace asc::std
```

This prototype corresponds to the headers: `<asc/std/memory>`, `<asc/std/tuple>`.

### Prototype 2

```cpp
namespace asc::std {
template<class... T, class Allocator> struct uses_allocator<asc::std::tuple<T...>, Allocator>;
} // namespace asc::std
```

This prototype corresponds to the headers: `<asc/std/memory>`, `<asc/std/tuple>`.

## Constraints

- The ordinary primary template yields `true` when `T::allocator_type` exists and the source allocator is convertible to that type; otherwise it yields `false`.
- The public specialization for `tuple` yields `true`; this type trait does not actually construct objects or guarantee that any constructor is available.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <memory>
#include <asc/std/memory>

struct Consumer { using allocator_type = ::std::allocator<int>; };

bool example()
{
    static_assert(asc::std::uses_allocator<Consumer, ::std::allocator<int>>::value);
    static_assert(!asc::std::uses_allocator<int, ::std::allocator<int>>::value);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_memory.md)
