# asc::std::ranges::owning_view::owning_view

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

`asc::std::ranges::owning_view::owning_view` initializes an `owning_view` object with the construction forms listed on this page.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

### Prototype 1

```cpp
owning_view();
```

### Prototype 2

```cpp
owning_view(owning_view<Rp>&& other);
```

### Prototype 3

```cpp
constexpr owning_view(Rp&& base) noexcept(is_nothrow_move_constructible_v<Rp>);
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | The construction source object; this object is initialized from its corresponding members or underlying state, and the rvalue form may move that state. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `base` | Input/Output | A reference to the object used to "initialize an `owning_view` object with the construction forms listed on this page"; the referenced object must be valid during the call. |

## Return Value

No return value.

## Constraints

- Element access and iteration on the view do not allocate additional storage; the underlying range's lifetime must cover all uses of borrowed views.
- owning_view only owns the range object passed in by the caller and performs no additional allocation.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/ranges>
#include <asc/std/array>
#include <asc/std/iterator>
#include <asc/std/tuple>

bool example()
{
    int values[] = {1, 2, 3, 4};
    using Base = asc::std::ranges::subrange<int*>;
    Base base(values, values + 4);
    asc::std::ranges::owning_view<asc::std::array<int, 4>> view(asc::std::array<int, 4>{1, 2, 3, 4});
    return *view.begin() == 1;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
