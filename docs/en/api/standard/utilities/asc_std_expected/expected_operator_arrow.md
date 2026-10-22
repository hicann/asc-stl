# asc::std::expected::`operator-`>

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

Header: `<asc/std/expected>`.

`asc::std::expected::operator->` returns a pointer that can be used to access members of the pointed-to object.

Standard semantics reference: [cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected).

## Function Prototype

The following is the declaration inside class `expected<Value, Error>`; Value and Error are the owning class template parameters.

```cpp
constexpr Value* operator->() noexcept;
```

```cpp
constexpr const Value* operator->() const noexcept;
```

## Parameters

No function parameters. Value and Error are the parameters of the owning expected class template.

## Return Value

Returns Value* or const Value*. Returns the address of the active success value; access requires has_value(), and the resulting pointer depends on the lifetime of the object and the current value.

## Constraints

- Supports all cv/ref-qualified forms.
- Callable objects and result construction on the device side must not throw exceptions.
- The returned reference, pointer, or non-owning wrapper does not extend the lifetime of the referenced object. The object must still be alive when used; it must not be accessed after the object is destroyed or after the lifetime of its value storage ends.

## Example

The following Host example checks the result while the referenced object is still alive.

```cpp
#include <asc/std/expected>

bool example()
{
    asc::std::expected<int, int> value(7);
    int* selected = value.operator->();
    *selected = 9;
    return value.has_value() && *value == 9;
}
```

## Related APIs

- [`asc::std::expected`](expected.md)
- [API list for this header](asc_std_expected.md)
