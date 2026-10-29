# asc::std::optional::value_or

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

Header: `<asc/std/optional>`.

`asc::std::optional::value_or` returns the contained value when the object is engaged, otherwise it returns the fallback value provided by the caller.

Standard semantics reference: [cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional).

## Function Prototype

Member of: [`asc::std::optional`](optional.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside class asc::std::optional; template parameters and other members are provided by the owning class.
template<class U> constexpr T value_or(U&& default_value)&&;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside class asc::std::optional; template parameters and other members are provided by the owning class.
template<class U> constexpr T value_or(U&& default_value) const&;
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `U` | The type of the fallback value; it must be convertible to T. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `default_value` | Input/Output | The fallback value; when this object contains no value, the T converted from it is returned, and when engaged, the contained value is returned (the rvalue overload returns it by move). |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `U` | The type of the fallback value; it must be convertible to T. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `default_value` | Input/Output | The fallback value; when this object contains no value, the T converted from it is returned, and when engaged, the contained value is returned. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `T` | Returns the contained value, otherwise the fallback value provided by the caller. |
| Prototype 2 | `T` | Returns the contained value, otherwise the fallback value provided by the caller. |

## Constraints

- T must be an ordinary non-reference object type.
- Host follows the valid C++17 operations.
- The operations that construction, assignment, invocation, and swap rely on must not throw on the device side.

## Example

The following Host snippet demonstrates the call with concrete types; the object must be confirmed to be in the engaged state before accessing the value.

```cpp
#include <asc/std/optional>

decltype(auto) example()
{
    asc::std::optional<int> value(7);
    return static_cast<asc::std::optional<int>&&>(value).value_or(0);
}

bool verify_example()
{
    return example() == 7;
}
```

## Related APIs

- [`asc::std::optional`](optional.md)
- [API list for this header](asc_std_optional.md)
