# asc::std::ranges::single_view::single_view

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

`asc::std::ranges::single_view::single_view` initializes a `single_view` object according to the construction forms listed on this page.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`single_view`](ranges_single_view.md). The following lists declaration summaries per the current implementation; selection parameters used only for SFINAE are omitted, and type defaults kept for calls are preserved. Each default construction form has its own participation constraint, so it must not be assumed that all specializations are default-constructible.

### Prototype 1

```cpp
constexpr single_view();
```

Participates only when T satisfies default_initializable.

### Prototype 2

```cpp
template<class T2 = T>
constexpr explicit single_view(const T2& value) noexcept(is_nothrow_copy_constructible_v<T2>);
```

T2 must be copy-constructible, and its remove_cvref_t must not be this single_view specialization.

### Prototype 3

```cpp
constexpr explicit single_view(T&& value) noexcept(is_nothrow_move_constructible_v<T>);
```

Explicitly moves and stores the single value.

### Prototype 4

```cpp
template<class... Args>
constexpr explicit single_view(in_place_t tag, Args&&... args)
    noexcept(is_nothrow_constructible_v<T, Args...>);
```

Participates only when T is constructible from Args....

## Parameters

### Parameters of Prototype 1

No function parameters.

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T2` | The type of the value copied from, defaulting to T. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The single value copied for storage; this argument is not borrowed. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The single value moved for storage; the state of the source object follows the move rules of T. |

### Parameters of Prototype 4

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Args` | The forwarded argument type pack for in-place construction of the stored value. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `tag` | Input | The in-place construction tag in_place. |
| `args` | Input | The construction arguments forwarded to the stored T with their original value categories. |

## Return Value

No return value.

## Constraints

- Each form must satisfy the participation constraints listed in its prototype; the actually stored range or value must also satisfy the type requirements of the owning view.
- Constructing the view does not copy the elements it borrows; the underlying storage and borrowed objects must cover the corresponding iterator and element access periods.
- Forms marked noexcept must satisfy the requirement that the actual member operations do not throw; for the exact exception specifications, see the prototypes.

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
    asc::std::ranges::single_view<int> view(7);
    return *view.begin() == 7;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
