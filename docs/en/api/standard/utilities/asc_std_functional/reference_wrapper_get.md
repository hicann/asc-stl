# asc::std::reference_wrapper::get

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

`asc::std::reference_wrapper::get` returns the reference to the object stored in the reference wrapper.

Standard semantics reference: [cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional).

## Function Prototype

Member of: [`asc::std::reference_wrapper`](reference_wrapper.md).

```cpp
// Excerpt of the declaration inside asc::std::reference_wrapper; the template parameters and other members are provided by the enclosing class.
[[nodiscard]] constexpr type& get() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `type &` | Returns the reference to the object stored in the reference wrapper. |

## Constraints

- Standard callable objects and pointer-to-member forms are supported.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/functional>

bool example()
{
    int value = 7;
    asc::std::reference_wrapper<int> reference(value);
    reference.get() = 9;
    return value == 9 && &reference.get() == &value;
}
```

## Related APIs

- [`asc::std::reference_wrapper`](reference_wrapper.md)
- [API list for this header](asc_std_functional.md)
