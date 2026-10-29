# asc::std::ranges::view_interface::operator bool

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

`asc::std::ranges::view_interface::operator bool` is provided by `<asc/std/ranges>`; it is the explicit boolean conversion of the view interface, which determines whether the range is empty through the empty-check customization point object. The interface follows the semantics of the corresponding C++ standard facility; the language modes and call sites of ASC-STL are governed by the declaration on this page.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`view_interface<Derived>`](ranges_view_interface.md). The following is a declaration summary with SFINAE selection parameters omitted; the two forms participate when ranges::empty is valid for Derived& and const Derived&, respectively.

```cpp
template<class Derived2 = Derived>
constexpr explicit operator bool();

template<class Derived2 = Derived>
constexpr explicit operator bool() const;
```

## Parameters

No function parameters; Derived2 defaults to Derived and is used to defer the empty query of the corresponding const form.

## Return Value

Returns true when non-empty and false when empty; the conversion is explicit and can be used in an if condition or an explicit static_cast<bool>.

## Constraints

- The ranges::empty query of the corresponding const form must be valid; this conversion only checks emptiness and does not take ownership of the elements.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/ranges>

template <class Object, class... Args>
decltype(auto) example(Object& object, Args&&... args)
{
    return object.operator bool(static_cast<Args&&>(args)...);
}

bool verify_example()
{
    int values[] = {1, 2};
    asc::std::ranges::ref_view<int[2]> view(values);
    return example(view);
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
