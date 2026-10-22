# asc::std::ranges::empty_view::end

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

Header: `<asc/std/ranges>`.

`asc::std::ranges::empty_view::end` returns an iterator to the past-the-end position.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`empty_view<T>`](ranges_empty_view.md). This member can be called without constructing an object.

```cpp
static constexpr T* end() noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `T *` | Returns an iterator to the past-the-end position. |

## Constraints

- Element access and iteration on the view do not allocate additional storage; the underlying range's lifetime must cover all uses of borrowed views.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/ranges>

static_assert(asc::std::ranges::empty_view<int>::end() == nullptr);
```

## Related APIs

- [`asc::std::ranges::empty_view`](ranges_empty_view.md)
- [API list for this header](asc_std_ranges.md)
