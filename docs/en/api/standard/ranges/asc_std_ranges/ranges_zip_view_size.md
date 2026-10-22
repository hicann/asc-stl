# asc::std::ranges::zip_view::size

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

`asc::std::ranges::zip_view::size` returns the number of elements contained in the current object.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`asc::std::ranges::zip_view`](ranges_zip_view.md). The following are in-class declarations, where `first_` and `second_` denote the two underlying views.

```cpp
constexpr asc::std::size_t size()
    noexcept(noexcept(asc::std::ranges::size(first_)) && noexcept(asc::std::ranges::size(second_)));
```

```cpp
constexpr asc::std::size_t size() const
    noexcept(noexcept(asc::std::ranges::size(first_)) && noexcept(asc::std::ranges::size(second_)));
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `asc::std::size_t` | The smaller of the sizes of the two underlying views, i.e. the number of element pairs that can be formed. |

## Constraints

- Both underlying views must support `asc::std::ranges::size`; the `const` overload additionally requires the size expressions on constant underlying views to be valid.
- The current `zip_view` combines two views that support random access and size queries; the underlying element storage it borrows must remain valid.
- This member does not traverse elements; when both underlying size queries do not throw, this member does not throw either.

## Example

The following Host example provides concrete inputs and checks the result.

```cpp
#include <asc/std/ranges>

bool example()
{
    int left[4] = {1, 2, 3, 4};
    int right[2] = {5, 6};
    using Base = asc::std::ranges::subrange<int*>;
    asc::std::ranges::zip_view<Base, Base> view(Base(left, left + 4), Base(right, right + 2));
    const auto& constant = view;
    return view.size() == 2 && constant.size() == 2;
}
```

## Related APIs

- [`asc::std::ranges::zip_view`](ranges_zip_view.md)
- [API list for this header](asc_std_ranges.md)
