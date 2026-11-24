# asc::tabulate_output_iterator

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

Each assignment invokes function(first+position,value) once and discards the result.

`<asc/iterator>`

## Declaration

```cpp
namespace asc {
template <class Function, class Index = asc::std::ptrdiff_t, class Difference = asc::std::ptrdiff_t>
class tabulate_output_iterator;
}  // namespace asc
```

## Constraints

Index is separate from the signed difference. Dereference and movement do not invoke the callback. Proxies retain the old index; explicitly capture any state shared across callable snapshots.

Supports C++17 and C++20. Stored callables are copyable; borrowed objects remain alive. Compare positions only in the same logical sequence. constexpr and conditional noexcept follow actual operations; internal constraint parameters and conditional exception specifications are omitted below.

## Example

```cpp
#include <asc/iterator>

bool example()
{
    int data[2] = {};
    auto f = [&](asc::std::ptrdiff_t n, int x) { data[n] = x; };
    asc::tabulate_output_iterator<decltype(f)> it(f);
    *it++ = 3;
    *it = 5;
    return data[0] == 3 && data[1] == 5;
}
```

## Related APIs

- [<asc/iterator>](asc_iterator.md)
