# asc::std::expected::value_or

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

`asc::std::expected::value_or` returns the value when the object has one, and otherwise returns the alternative value provided by the caller.

Standard semantics reference: [cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected).

## Function Prototype

The following is the declaration inside class `expected<Value, Error>`; Value and Error are the owning class template parameters.

```cpp
constexpr Value value_or(const Value& fallback) const;
```

```cpp
template<class Up> constexpr Value value_or(Up&& fallback) const&;
```

```cpp
template<class Up> constexpr Value value_or(Up&& fallback) &&;
```

## Parameters

**Template Parameters (template overload)**

| Parameter | Description |
| --- | --- |
| `Up` | The source type of the alternative value; must be convertible to Value. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `fallback` | Input/Output (forwarded form) | Used as the alternative value in the corresponding state; an rvalue source may be moved. |

## Return Value

Returns Value. When there is a value, the success value is copied or moved; otherwise fallback is converted to Value.

## Constraints

- The owning expected<Value, Error> requires a valid non-void value type and an error object type; the current operation must also satisfy the prototype, parameter, and state requirements on this page. The propagation of the success value or the error value is constrained respectively by the callable and constructible conditions of the corresponding cv/ref form.

## Example

The following Host snippet demonstrates the call with concrete types; confirm the object is in the value state before accessing the value.

```cpp
#include <asc/std/expected>

decltype(auto) example()
{
    asc::std::expected<int, int> value(7);
    return value.value_or(0);
}

bool verify_example()
{
    return example() == 7;
}
```

## Related APIs

- [`asc::std::expected`](expected.md)
- [API list for this header](asc_std_expected.md)
