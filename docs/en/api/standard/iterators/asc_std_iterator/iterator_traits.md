# asc::std::iterator_traits

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

Header: `<asc/std/iterator>`.

`asc::std::iterator_traits` obtains the corresponding iterator property types at compile time.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

```cpp
namespace asc::std {
template<class Iter, class = void>
struct iterator_traits;
}
```

The primary template allows the second template parameter to be omitted. For iterators that provide the five legacy associated types, the traits copy their nested types; when the selection condition is not satisfied, the primary template may be empty. Object pointers have the following partial specialization:

```cpp
namespace asc::std {
template<class T>
struct iterator_traits<T*, enable_if_t<is_object_v<T>>> {
    using difference_type = ptrdiff_t;
    using value_type = remove_cv_t<T>;
    using pointer = T*;
    using reference = T&;
    using iterator_category = random_access_iterator_tag;
    using iterator_concept = contiguous_iterator_tag;
};
}
```

The object-pointer specialization accepts ordinary pointers and Device GM/UB object pointers. `pointer` and `reference` preserve the original address space; `void*` and function pointers do not match this specialization.

## Constraints

- Provides the C++20 public iterator concepts and traits interfaces.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>
#include <asc/std/type_traits>

bool example()
{
    struct custom_iterator {
        using difference_type = short;
        using value_type = long;
        using pointer = long*;
        using reference = long&;
        using iterator_category = asc::std::input_iterator_tag;
    };
    using generic_traits = asc::std::iterator_traits<custom_iterator>;
    using pointer_traits = asc::std::iterator_traits<const int*>;
    static_assert(asc::std::is_same_v<generic_traits::difference_type, short>);
    static_assert(asc::std::is_same_v<generic_traits::iterator_category, asc::std::input_iterator_tag>);
    static_assert(asc::std::is_same_v<pointer_traits::value_type, int>);
    static_assert(asc::std::is_same_v<pointer_traits::iterator_concept, asc::std::contiguous_iterator_tag>);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
