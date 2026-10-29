# asc::std::expected::or_else

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

`asc::std::expected::or_else` calls the recovery function when an error is held, and keeps the success value.

Standard semantics reference: [cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected).

## Function Prototype

The following is inside class `expected<Value, Error>`. The return type is determined by the call result of function and the value/error propagation rules of this operation.

```cpp
template<class Fun>
constexpr auto or_else(Fun&& function) &;
```

```cpp
template<class Fun>
constexpr auto or_else(Fun&& function) const&;
```

```cpp
template<class Fun>
constexpr auto or_else(Fun&& function) &&;
```

```cpp
template<class Fun>
constexpr auto or_else(Fun&& function) const&&;
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Fun` | The callable object type accepting the error with the corresponding cv/ref qualification; the expected returned by the function is used as the result. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `function` | Input/Output | Called with the error only when the object is in the error state; arguments are passed according to the &, const&, &&, or const&& form of this object. |

## Return Value

Returns an expected state object: the called branch uses the expected returned by the function as the result; the uncalled branch propagates the original success value. The lvalue form propagates from the corresponding lvalue, and the rvalue form may move; the return type is determined by the callable result and the corresponding state type.

## Constraints

- Fun is the only member template parameter; the caller does not provide additional success-value or error template parameters. The callable result and the state of the uncalled branch must satisfy the construction and type-matching requirements.

- Supports all cv/ref-qualified forms.
- Callable objects and result construction on the device side must not throw exceptions.

## Example

The following Host snippet demonstrates the call with concrete types; confirm the object is in the value state before accessing the value.

```cpp
#include <asc/std/expected>

decltype(auto) example()
{
    asc::std::expected<int, int> value(asc::std::unexpect, 3);
    auto next = value.or_else([](int) { return asc::std::expected<int, int>(7); });
    return next;
}

bool verify_example()
{
    const auto result = example();
    return result.has_value() && *result == 7;
}
```

## Related APIs

- [`asc::std::expected`](expected.md)
- [API list for this header](asc_std_expected.md)
