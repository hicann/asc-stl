# asc::std::incrementable_traits

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

`asc::std::incrementable_traits` obtains the corresponding iterator property type at compile time.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

### Prototype 1

```cpp
namespace asc::std {
template<class Index> struct incrementable_traits;
} // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template<class T> struct incrementable_traits;
} // namespace asc::std
```

## Constraints

- Provides the C++20 public iterator concepts and traits interfaces.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/vector>
#include <asc/std/forward_list>

bool example()
{
    static_assert(asc::std::is_same_v<asc::std::incrementable_traits<int*>::difference_type, asc::std::ptrdiff_t>);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
