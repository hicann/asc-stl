# asc::std::bind_front

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

`asc::std::bind_front` fixes call arguments at the front of the function object's argument list.

Standard semantics reference: [cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional).

## Function Prototype

```cpp
namespace asc::std {
template<class Fn, class ...Args> constexpr auto bind_front(Fn&& function, Args&&... args) noexcept(is_nothrow_constructible_v<tuple<decay_t<Args>...>, Args&&...>);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Fn` | The type of the function, function pointer, member pointer, or function object to be invoked. |
| `Args` | The list of argument types passed to the constructor or the callable object. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `function` | Input/Output | A reference to the object used by "fix call arguments at the front of the function object's argument list"; the referenced object must remain valid for the duration of the call. |
| `args` | Input/Output | The list of arguments forwarded to object construction or the function call. |

## Return Value

| Return type | Description |
| --- | --- |
| `auto` | Returns a callable object or a reference wrapper that stores the call target and the selected arguments. |

## Constraints

- Standard callable objects and member pointer forms are supported.

## Example

The following Host snippet demonstrates the interface call with concrete objects.

```cpp
#include <asc/std/functional>

decltype(auto) example()
{
    auto bound = asc::std::bind_front([](int left, int right) { return left + right; }, 2);
    return bound(3);
}
```

## Related APIs

- [API list for this header](asc_std_functional.md)
