# asc::std::not_fn

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

`asc::std::not_fn` creates a wrapper that takes the logical negation of a function object's result.

Standard semantics reference: [cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional).

## Function Prototype

```cpp
namespace asc::std {
template<class Fn> [[nodiscard]] constexpr auto not_fn(Fn&& function);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Fn` | Type of the function, function pointer, pointer to member, or function object being called. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `function` | Input/Output | Reference to the object used for "creating a wrapper that takes the logical negation of a function object's result"; the referenced object must remain valid during the call. |

## Return Value

| Return type | Description |
| --- | --- |
| `auto` | Returns the callable object or reference wrapper that stores the call target and the selected arguments. |

## Constraints

- Standard callable objects and pointer-to-member forms are supported.

## Example

The following Host snippet shows the interface call with concrete objects.

```cpp
#include <asc/std/functional>

decltype(auto) example()
{
    auto call = asc::std::not_fn([](int value) { return value > 0; });
    return call(-1);
}
```

## Related APIs

- [API list for this header](asc_std_functional.md)
