# asc::std::optional<T&>::`operator=`

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

`asc::std::optional<T&>::operator=` updates the object with the selected assignment overload and returns the specified result.

Standard semantics reference: [cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional).

## Function Prototype

### Prototype 1

```cpp
// Excerpt of the declaration inside class asc::std::optional<T&>; template parameters and other members are provided by the owning class.
constexpr asc::std::optional<T&>& operator=(asc::std::nullopt_t) noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside class asc::std::optional<T&>; template parameters and other members are provided by the owning class.
constexpr asc::std::optional<T&>& operator=(const asc::std::optional<T&>&) noexcept;
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `asc` | Input | The nullopt_t empty-state tag (the nullopt constant); after assignment the current optional no longer references any object. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `parameter 1` | Input | The source optional<T&> of the copy; the current object rebinds to the same target it references, and the referenced object itself is not modified. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `asc::std::optional<T&>&` | Returns a reference to the updated current object, which can continue to be assigned or used in compound operations. |
| Prototype 2 | `asc::std::optional<T&>&` | Returns a reference to the updated current object, which can continue to be assigned or used in compound operations. |

## Constraints

- The reference specialization only allows safe same-type lvalue binding.
- Borrowed-pointer semantics are adopted; conversions that easily produce dangling references are not provided.

## Example

The following Host snippet demonstrates the call with concrete types; the object must be confirmed to be in the engaged state before accessing the value.

```cpp
#include <asc/std/optional>

bool example()
{
    int value = 7;
    asc::std::optional<int&> reference(value);
    reference = asc::std::nullopt;
    return !reference.has_value() && value == 7;
}
```

## Related APIs

- [API list for this header](asc_std_optional.md)
