# asc::std::ranges::iota_view::iota_view

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

`asc::std::ranges::iota_view::iota_view` initializes an `iota_view` object with the construction forms listed on this page.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`iota_view`](ranges_iota_view.md). The following lists declaration summaries by the current implementation; selection parameters used only for SFINAE are omitted, and type defaults used for calls are kept. Default construction forms each have per-form participation conditions; do not assume all specializations are default constructible based on this.

### Prototype 1

```cpp
constexpr iota_view();
```

Participates only when Value satisfies default_initializable; the stored start and Bound are both value-initialized.

### Prototype 2

```cpp
constexpr explicit iota_view(Value value) noexcept;
```

Explicitly stores the start, with the bound value-initialized; when the default Bound is unreachable_sentinel_t, an unbounded incrementing sequence results.

### Prototype 3

```cpp
constexpr iota_view(type_identity_t<Value> value, type_identity_t<Bound> bound_sentinel) noexcept;
```

Stores the start and a bound not included in the result; the required end position must be reachable under the increment and comparison rules.

### Prototype 4

```cpp
template<class Bound2 = Bound>
constexpr iota_view(iterator first, iterator last) noexcept;
```

Participates only when same_as<Value, Bound2>; iterator is the counting iterator already exposed by this type.

### Prototype 5

```cpp
template<class Bound2 = Bound>
constexpr iota_view(iterator first, Bound2 last) noexcept;
```

Participates only when same_as<Bound2, unreachable_sentinel_t>.

### Prototype 6

There is also a constructor taking the current counting iterator and the implementation sentinel, with a Bound2=Bound selection parameter, under the condition !same_as<Value, Bound2> && !same_as<Value, unreachable_sentinel_t>. Normal heterogeneous bounded specializations can pass begin() and end() of the original view; the implementation name of the sentinel is not declared as a public type. This constructor is likewise constexpr and noexcept.

## Parameters

### Parameters of Prototype 1

No function parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The start of the counting sequence. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The start of the counting sequence. |
| `bound_sentinel` | Input | The exclusive end value or sentinel. |

### Parameters of Prototype 4

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Bound2` | The type used to select the bound construction, defaulting to Bound. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The current view iterator that determines the new start. |
| `last` | Input | The current view iterator that determines the new exclusive bound value. |

### Parameters of Prototype 5

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Bound2` | The type used to select the bound construction, defaulting to Bound. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The current view iterator that determines the new start. |
| `last` | Input | The unreachable sentinel, producing an unbounded end condition. |

### Parameters of Prototype 6

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The counting iterator that determines the new start. |
| `last` | Input | The heterogeneous bounded sentinel obtained from the same iota specialization, holding the original bound value. |

## Return Value

No return value.

## Constraints

- Each form must satisfy the participation conditions listed in its prototype; the actually stored range or value must also satisfy the type requirements of the owning view.
- Constructing the view does not copy the elements it borrows; the underlying storage and borrowed objects must cover the corresponding iterator and element access periods.
- Forms marked noexcept must satisfy the requirement that the actual member operations do not throw; see each prototype for the specific exception specification.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/ranges>

bool example()
{
    asc::std::ranges::iota_view<int> unbounded(3);
    asc::std::ranges::iota_view<int, int> original(3, 7);
    asc::std::ranges::iota_view<int, int> selected(original.begin() + 1, original.end());
    return *unbounded.begin() == 3 && *selected.begin() == 4 && selected.size() == 3;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
