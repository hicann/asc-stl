# asc::make_transform_output_iterator

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

Constructs the adaptor, deducing and owning its state. Returns a write proxy owning position and callable snapshots. Assignment forwards the argument, transforms once and stores once.

`<asc/iterator>`

## Declaration

```cpp
namespace asc {
template <class I, class F>
constexpr transform_output_iterator<asc::std::decay_t<F>, I> make_transform_output_iterator(I current, F&& function);
}  // namespace asc
```

## Constraints

Const data is not writable. A const proxy can assign and survive its temporary adaptor while borrowed targets remain valid. Postincrement retains the old target for *it++ = value. Callable snapshots may have side effects.

Supports C++17 and C++20. Stored callables are copyable; borrowed objects remain alive. Compare positions only in the same logical sequence. constexpr and conditional noexcept follow actual operations; internal constraint parameters and conditional exception specifications are omitted below.

## Example

```cpp
#include <asc/iterator>

bool example()
{
    int data[2] = {};
    auto f = [](int x) { return x * 2; };
    auto it = asc::make_transform_output_iterator(data, f);
    *it++ = 3;
    *it = 4;
    return data[0] == 6 && data[1] == 8;
}
```

## Related APIs

- [<asc/iterator>](asc_iterator.md)
