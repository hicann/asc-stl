# asc::std::pointer_traits::difference_type

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

`asc::std::pointer_traits::difference_type` identifies the signed type for iterator distances.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Declaration

The following queries the actual type through the public traits; queried_type is an example name, not an additional public member.

Difference type: a generic pointer prefers `Ptr::difference_type`, otherwise it is `ptrdiff_t`; the raw-pointer specialization is `ptrdiff_t`.

```cpp
template<class Ptr>
using queried_type = typename asc::std::pointer_traits<Ptr>::difference_type;
```

## Constraints

- Difference type: a generic pointer prefers `Ptr::difference_type`, otherwise it is `ptrdiff_t`; the raw-pointer specialization is `ptrdiff_t`.
- The pointer type must allow extracting the element type and satisfy the queried member requirements; the type query accesses no objects and allocates no storage.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/memory>
#include <asc/std/type_traits>

template<class T>
struct example_pointer {
    using element_type = T;
    using difference_type = long;
    template<class U> using rebind = example_pointer<U>;
};

using traits = asc::std::pointer_traits<example_pointer<int>>;
static_assert(asc::std::is_same_v<typename traits::difference_type, long>);
static_assert(asc::std::is_same_v<asc::std::pointer_traits<int*>::rebind<double>, double*>);
```

## Related APIs

- [`asc::std::pointer_traits`](pointer_traits.md)
- [API list for this header](asc_std_memory.md)
