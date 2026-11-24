# asc::make_zip_iterator

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

Constructs the adaptor, deducing and owning its state. Combines one or more positions into an unspecified tuple-protocol proxy with bindings, ADL get, value conversion and const assignment.

`<asc/iterator>`

## Declaration

```cpp
namespace asc {
template <class... I>
constexpr zip_iterator<I...> make_zip_iterator(I... current);
}  // namespace asc
```

## Constraints

Navigation follows the weakest component; a whole-tuple write requires all targets writable. Equality checks all positions and distances agree. The caller supplies a common length; physical ends of unequal ranges cannot be combined.

Supports C++17 and C++20. Stored callables are copyable; borrowed objects remain alive. Compare positions only in the same logical sequence. constexpr and conditional noexcept follow actual operations; internal constraint parameters and conditional exception specifications are omitted below.

## Example

```cpp
#include <asc/iterator>

bool example()
{
    int a[2] = {1, 2}, b[2] = {10, 20};
    auto it = asc::make_zip_iterator(a, b);
    *it = asc::std::tuple<int, int>{3, 30};
    return a[0] == 3 && b[0] == 30;
}
```

## Related APIs

- [<asc/iterator>](asc_iterator.md)
