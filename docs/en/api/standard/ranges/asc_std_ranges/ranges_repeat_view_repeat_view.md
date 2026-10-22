# asc::std::ranges::repeat_view::repeat_view

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

`asc::std::ranges::repeat_view::repeat_view` initializes a `repeat_view` object according to the construction forms listed on this page.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`repeat_view`](ranges_repeat_view.md). The following lists declaration summaries per the current implementation; selection parameters used only for SFINAE are omitted, and type defaults kept for calls are preserved. Each default construction form has its own participation constraint, so it must not be assumed that all specializations are default-constructible.

### Prototype 1

```cpp
constexpr repeat_view();
```

Participates only when T satisfies default_initializable; the stored value is default-constructed and Bound is value-initialized. When the default Bound=ptrdiff_t is used, the repetition count is 0.

### Prototype 2

```cpp
template<class T2 = T>
constexpr explicit repeat_view(const T2& value, Bound bound_sentinel);
```

T2 must satisfy copy_constructible and must not be this repeat_view specialization.

### Prototype 3

```cpp
constexpr explicit repeat_view(T&& value, Bound bound_sentinel);
```

Moves the stored value; T is not copied on each dereference.

### Prototype 4

```cpp
template<class... TArgs, class... BoundArgs>
constexpr explicit repeat_view(piecewise_construct_t tag, tuple<TArgs...> value_args,
    tuple<BoundArgs...> bound_args);
```

T and Bound must each be constructible from the corresponding parameter packs.

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
| `value` | Input | The repeated value copied for storage; all iterators dereference the same stored value, yielding a const T&. |
| `bound_sentinel` | Input | The non-negative repetition count, or the unreachable_sentinel_t object used by that specialization; no default argument. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The repeated value moved for storage. |
| `bound_sentinel` | Input | The non-negative repetition count for bounded specializations, or unreachable_sentinel_t for unbounded specializations. |

### Parameters of Prototype 4

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `TArgs` | The parameter type pack for constructing the repeated value T. |
| `BoundArgs` | The parameter type pack for constructing the bound Bound. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `tag` | Input | The piecewise construction tag. |
| `value_args` | Input | The parameter tuple used to construct the stored value T. |
| `bound_args` | Input | The parameter tuple used to construct the bound Bound. |

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
    asc::std::ranges::repeat_view<int, int> view(7, 3);
    return *view.begin() == 7;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
