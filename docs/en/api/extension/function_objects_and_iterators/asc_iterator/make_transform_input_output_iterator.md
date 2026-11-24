# asc::make_transform_input_output_iterator

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

Constructs the adaptor, deducing and owning its state. A proxy reads and stores logical values through separate input and output transformations.

`<asc/iterator>`

## Declaration

```cpp
namespace asc {
template <class I, class In, class Out>
constexpr transform_input_output_iterator<asc::std::decay_t<In>, asc::std::decay_t<Out>, I>
make_transform_input_output_iterator(I current, In&& input, Out&& output);
}  // namespace asc
```

## Constraints

The base is at least forward; the read callable is stable and const-callable. A write must read back the same logical value. Use directional adaptors for lossy conversion. Movement and swapping require the appropriate logical writeback laws.

Supports C++17 and C++20. Stored callables are copyable; borrowed objects remain alive. Compare positions only in the same logical sequence. constexpr and conditional noexcept follow actual operations; internal constraint parameters and conditional exception specifications are omitted below.

## Example

```cpp
#include <asc/iterator>

bool example()
{
    unsigned stored = 0;
    auto f = [](unsigned x) { return x ^ 0x80u; };
    auto it = asc::make_transform_input_output_iterator(&stored, f, f);
    *it = 7u;
    unsigned value = *it;
    return stored == 135u && value == 7u;
}
```

## Related APIs

- [<asc/iterator>](asc_iterator.md)
