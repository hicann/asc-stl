# asc::std::ranges::owning_view::base

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

`asc::std::ranges::owning_view::base` returns the underlying iterator or object stored by the adaptor.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`owning_view`](ranges_owning_view.md). The following is a declaration summary listed by participation conditions; template defaults used for calls are kept, and implementation-selection parameters used only for SFINAE are omitted. When a private return type is involved, it is summarized as auto; this does not promise the type can be named directly.

### Prototype 1

```cpp
constexpr Range& base() & noexcept;
```

This form has no additional member template participation condition; the requirements of the enclosing type must still be satisfied.

### Prototype 2

```cpp
constexpr const Range& base() const& noexcept;
```

This form has no additional member template participation condition; the requirements of the enclosing type must still be satisfied.

### Prototype 3

```cpp
constexpr Range&& base() && noexcept;
```

This form has no additional member template participation condition; the requirements of the enclosing type must still be satisfied.

### Prototype 4

```cpp
constexpr const Range&& base() const&& noexcept;
```

This form has no additional member template participation condition; the requirements of the enclosing type must still be satisfied.

## Parameters

### Parameters of Prototype 1

No function parameters.

### Parameters of Prototype 2

No function parameters.

### Parameters of Prototype 3

No function parameters.

### Parameters of Prototype 4

No function parameters.

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `Range&` | Returns the stored underlying range; the const lvalue form copies, the rvalue form moves, and the forms of owning_view return the corresponding reference as declared. When returning a reference or a borrowed range, the original storage's lifetime must be observed. |
| Prototype 2 | `const Range&` | Returns the stored underlying range; the const lvalue form copies, the rvalue form moves, and the forms of owning_view return the corresponding reference as declared. When returning a reference or a borrowed range, the original storage's lifetime must be observed. |
| Prototype 3 | `Range&&` | Returns the stored underlying range; the const lvalue form copies, the rvalue form moves, and the forms of owning_view return the corresponding reference as declared. When returning a reference or a borrowed range, the original storage's lifetime must be observed. |
| Prototype 4 | `const Range&&` | Returns the stored underlying range; the const lvalue form copies, the rvalue form moves, and the forms of owning_view return the corresponding reference as declared. When returning a reference or a borrowed range, the original storage's lifetime must be observed. |

## Constraints

- The participation condition of each form is shown in the prototype; no-argument queries are generally called directly without specifying a template selection type.
- Returned iterators, pointers, or references, as well as borrowed ranges, must not outlive the validity of the view objects and element storage they actually depend on.

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
    return *asc::std::ranges::begin(view.base()) == 1;
}
```

## Related APIs

- [`asc::std::ranges::owning_view`](ranges_owning_view.md)
- [API list for this header](asc_std_ranges.md)
