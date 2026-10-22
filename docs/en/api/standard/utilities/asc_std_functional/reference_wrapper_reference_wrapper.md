# asc::std::reference_wrapper::reference_wrapper

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

Header: `<asc/std/functional>`.

`asc::std::reference_wrapper::reference_wrapper` initializes a `reference_wrapper` object with the constructor forms listed on this page.

Standard semantics reference: [cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional).

## Function Prototype

The following is an **equivalent call form summary** inside the class; it expresses the exception conditions of reference binding with public type traits and omits the implementation's selection parameters.

```cpp
template<class U>
constexpr reference_wrapper(U&& value) noexcept(is_nothrow_convertible_v<U, T&>);
```

## Parameters

The unnamed template constraint parameters in the declaration select the available overloads and need not be provided by the caller; see the Constraints section for the applicable types and call conditions of the interface.

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `U` | Source type of the wrapped object; it must be bindable as an lvalue reference (U& valid) and must not be reference_wrapper itself. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | Source of the wrapped object; the constructed reference_wrapper stores a reference to the object, does not own it, and the object's lifetime must cover the wrapper's period of use. |

## Return Value

No return value.

## Constraints

- U must be implicitly bindable or convertible to T&; the constructor template excludes reference_wrapper of the same type, and an ordinary copy uses its implicit special members. The exception specification is determined by whether that reference conversion throws, not by copying the referenced object.

- The source value must be bindable as a valid `T&`; a temporary object must not be used to establish a reference that would dangle afterwards.
- The constructed wrapper does not own the object; the referenced object must remain valid while the wrapper is accessed.
- The constructor template excludes wrappers of the same type; an ordinary copy can still copy the reference relationship of an existing wrapper.

## Example

The following Host example uses a concrete object and checks the result of the call.

```cpp
#include <asc/std/functional>

bool example()
{
    int value = 3;
    asc::std::reference_wrapper<int> reference(value);
    reference.get() = 7;
    return value == 7 && &reference.get() == &value;
}
```

## Related APIs

- [API list for this header](asc_std_functional.md)
