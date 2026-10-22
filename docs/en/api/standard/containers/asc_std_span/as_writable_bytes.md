# asc::std::as_writable_bytes

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

Header: `<asc/std/span>`.

`asc::std::as_writable_bytes` converts a writable span to a writable byte view without owning the storage.

Standard semantics reference: [cppreference `span`](https://en.cppreference.com/w/cpp/header/span).

## Function Prototype

```cpp
namespace asc::std {
template<class T, size_t Extent>
constexpr auto as_writable_bytes(span<T, Extent> value) noexcept
    -> span<byte, Extent == dynamic_extent ? dynamic_extent : Extent * sizeof(T)>;
}
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The element type of the span; the byte view length is computed from the element count and sizeof(T). |
| `Extent` | The compile-time element count of the span; when it is dynamic_extent, the byte view length is also dynamic. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The source span to convert; its element storage is reinterpreted as writable bytes (span<byte>), and writing through the byte view modifies the source elements. |

## Return Value

| Return type | Description |
| --- | --- |
| `auto` | Returns a non-owning byte view observing the same storage; the original span does not transfer ownership. |

## Constraints

- Fixed or dynamic extents are supported, as well as pointers, arrays, and compatible contiguous ranges.
- In AI Core SIMD programming, this can be used only when the element pointer or range is representable as a standard plain pointer; no non-standard GM/UB pointer overload is provided.
- The returned byte view does not own the storage; the original range represented by values must cover the entire lifetime of the view's use.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/span>

bool example()
{
    int values[4] = {1, 2, 3, 4};
    const asc::std::span<int> view(values);
    const auto bytes = asc::std::as_writable_bytes(view);
    return bytes.size() == sizeof(values) && bytes.data() ==
        reinterpret_cast<asc::std::byte*>(values);
}
```

## Related APIs

- [API list for this header](asc_std_span.md)
