# asc::std::pointer_traits

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

Header: `<asc/std/memory>`.

`asc::std::pointer_traits` provides uniform access to the element type and address operations of pointer-like objects.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Declaration

The first line is the primary template and the second is the raw-pointer partial specialization; the second template parameter is a default selection parameter, and calls usually just write pointer_traits<Ptr>.

```cpp
namespace asc::std {
template<class Ptr, class = void> struct pointer_traits;
template<class T> struct pointer_traits<T*>;
}
```

## Constraints

- A raw pointer `T*` directly provides `pointer=T*`, `element_type=T`, `difference_type=ptrdiff_t`, and `rebind<U>=U*`.
- A generic pointer prefers its own `element_type`; if absent, it can be deduced from the first type argument of the `SomePointer<T, Args...>` form. When no element type can be obtained, these members are not provided.
- The generic `difference_type` prefers the pointer type's own member, otherwise it is `ptrdiff_t`; `rebind` prefers the pointer's alias of the same name, otherwise the first type argument of the template form above is replaced.
- No storage is allocated; the pointer returned by `pointer_to` has a usable period limited by the lifetime of the original object.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/memory>

bool example()
{
    int value = 7;
    int* pointer = asc::std::pointer_traits<int*>::pointer_to(value);
    return pointer == &value && *pointer == 7;
}
```

## Related APIs

- [API list for this header](asc_std_memory.md)
