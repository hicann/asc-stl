# asc::std::expected::error_or

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

`asc::std::expected::error_or` returns the error value when there is an error, and otherwise returns the alternative value given by the caller.

Standard semantics reference: [cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected).

## Function Prototype

The following is the declaration inside class `expected<Value, Error>`; Value and Error are the owning class template parameters.

```cpp
template<class G> constexpr Error error_or(G&& default_error) const&;
```

```cpp
template<class G> constexpr Error error_or(G&& default_error) &&;
```

## Parameters

**Template Parameters (template overload)**

| Parameter | Description |
| --- | --- |
| `G` | The source type of the alternative value; must be convertible to Error. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `default_error` | Input/Output (forwarded form) | Used as the alternative value in the corresponding state; an rvalue source may be moved. |

## Return Value

Returns Error. When there is a value, default_error is converted to Error; otherwise the stored error is copied or moved.

## Constraints

- Supports all cv/ref-qualified forms.
- Callable objects and result construction on the device side must not throw exceptions.

## Example

The following Host snippet demonstrates the call with concrete types; confirm the object is in the value state before accessing the value.

```cpp
#include <asc/std/expected>

decltype(auto) example()
{
    asc::std::expected<int, int> value(asc::std::unexpect, 3);
    return static_cast<asc::std::expected<int, int>&&>(value).error_or(0);
}

bool verify_example()
{
    return example() == 3;
}
```

## Related APIs

- [`asc::std::expected`](expected.md)
- [API list for this header](asc_std_expected.md)
