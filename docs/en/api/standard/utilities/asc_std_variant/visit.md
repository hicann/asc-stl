# asc::std::visit

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

Header: `<asc/std/variant>`.

`asc::std::visit` invokes the visitor with the active alternative and returns the result.

Standard semantics reference: [cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant).

## Function Prototype

The following is a public **call-form summary**; for three or more arguments the deduced result is computed as the common type of the invocation results over all combinations of active alternatives, and the implementation's helper types are omitted.

```cpp
namespace asc::std {
template<class Visitor, class Variant>
constexpr decltype(auto) visit(Visitor&& visitor, Variant&& value);
}
```

```cpp
namespace asc::std {
template<class Visitor, class Left, class Right>
constexpr decltype(auto) visit(Visitor&& visitor, Left&& left, Right&& right);
}
```

```cpp
namespace asc::std {
template<class Visitor, class First, class Second, class... Rest, enable_if_t<(sizeof...(Rest) >= 1), int> = 0>
constexpr auto visit(Visitor&& visitor, First&& first, Second&& second, Rest&&... rest);
}
```

```cpp
namespace asc::std {
template<class Result, class Visitor, class... Variants>
constexpr Result visit(Visitor&& visitor, Variants&&... variants);
}
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Visitor` | The visitor's callable type. |
| `Variant` | The type of the variant being visited. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `visitor` | Input | The visitor invoked with the current active alternative. |
| `value` | Input | The variant being visited. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Visitor` | The visitor's callable type. |
| `Left`, `Right` | The two variant types being visited. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `visitor` | Input | The visitor invoked with the combination of the two variants' active alternatives. |
| `left`, `right` | Input | The two variants being visited. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Visitor` | The visitor's callable type. |
| `First`, `Second`, `Rest...` | The three or more variant types being visited. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `visitor` | Input | The visitor invoked with the combination of each variant's active alternative. |
| `first`, `second`, `rest...` | Input | The three or more variants being visited. |

## Return Value

The default entry computes the common type of the invocation results over all possible combinations of active alternatives and converts the actual result to that type; even though the declaration uses decltype(auto), it does not guarantee preservation of the reference or value category returned by the visitor. The explicit Result entry further converts the default visit result to Result, requiring that conversion to be valid.

## Constraints

- Before the call, every `variant` being visited must have an active alternative; check `valueless_by_exception()` first, and an object with no active alternative must not be visited.

- At least one variant must be provided, and all inputs must hold a valid active alternative before the visit. The visitor must be callable for the required combinations of alternatives and the results must have a common type; the explicit Result form still relies on the default entry's result computation.

- Alternative types on the device side and the selected construction, assignment, and swap operations must not throw.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/variant>
#include <asc/std/type_traits>

struct value_reference {
    int& operator()(int& value) const { return value; }
};

bool example()
{
    asc::std::variant<int> value(7);
    static_assert(asc::std::is_same_v<decltype(asc::std::visit(value_reference{}, value)), int>);
    const auto result = asc::std::visit(value_reference{}, value);
    const long converted = asc::std::visit<long>(value_reference{}, value);
    return result == 7 && converted == 7L;
}
```

## Related APIs

- [API list for this header](asc_std_variant.md)
