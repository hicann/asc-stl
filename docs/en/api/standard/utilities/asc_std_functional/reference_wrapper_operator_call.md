# asc::std::reference_wrapper::`operator()`

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

`asc::std::reference_wrapper::operator()` processes the current object and the operands according to the operator rules available for `reference_wrapper`.

Standard semantics reference: [cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional).

## Function Prototype

Member of: [`asc::std::reference_wrapper`](reference_wrapper.md).

```cpp
// Excerpt of the declaration inside asc::std::reference_wrapper; the template parameters and other members are provided by the enclosing class.
template<class ...ArgTypes> constexpr invoke_result_t<type&, ArgTypes...> operator()(ArgTypes&&... args) const noexcept(is_nothrow_invocable_v<T&, ArgTypes...>);
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ArgTypes` | List of argument types forwarded to the wrapped callable object. |

## Return Value

| Return type | Description |
| --- | --- |
| `invoke_result_t<type &, ArgTypes...>` | Returns the result of invoking the function object with the selected arguments. |

## Constraints

- Standard callable objects and pointer-to-member forms are supported.

## Example

The following Host snippet demonstrates the call with concrete types; the input ranges and objects must remain valid during use.

```cpp
#include <asc/std/functional>

struct function_object { int operator()(int value) const { return value + 1; } };

decltype(auto) example(function_object& function)
{
    asc::std::reference_wrapper<function_object> reference(function);
    return reference(7);
}

bool verify_example()
{
    function_object function;
    return example(function) == 8;
}
```

## Related APIs

- [`asc::std::reference_wrapper`](reference_wrapper.md)
- [API list for this header](asc_std_functional.md)
