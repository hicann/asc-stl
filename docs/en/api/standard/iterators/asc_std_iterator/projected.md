# asc::std::projected

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

`asc::std::projected` applies the projection function to the iterator's reference type for use in range algorithm constraint checks.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

```cpp
namespace asc::std {
template<class It, class Proj, class = void>
struct projected;
}
```

When `indirect_result_t<Proj&, It>` is valid, the corresponding specialization and the `value_type` of the projection result are provided. This type is used for algorithm constraints and does not denote an actual projection iterator that can be created and dereferenced at run time.

## Constraints

- Provides the C++20 public iterator concepts and traits interfaces.

## Example

The following Host snippet instantiates the interface on this page with concrete iterator or container types.

```cpp
#include <asc/std/iterator>

#include <asc/std/type_traits>

struct example_identity { int& operator()(int& value) const { return value; } };

void example()
{
    using selected = asc::std::projected<int*, example_identity>;
    static_assert(asc::std::is_same_v<typename selected::value_type, int>);
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
