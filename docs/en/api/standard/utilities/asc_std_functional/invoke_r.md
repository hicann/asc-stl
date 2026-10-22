# asc::std::invoke_r

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

`asc::std::invoke_r` invokes according to the standard INVOKE rules and converts the result to the specified type.

Standard semantics reference: [cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional).

## Function Prototype

```cpp
namespace asc::std {
template<class Ret, class Fn, class ...Args> constexpr Ret invoke_r(Fn&& function, Args&&... arguments) noexcept(is_nothrow_invocable_r_v<Ret, Fn, Args...>);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Ret` | The call result type to convert to; when it is void, the call is only performed and its return value is discarded. |
| `Fn` | The type of the function, function pointer, member pointer, or function object to be invoked. |
| `Args` | The list of argument types passed to the constructor or the callable object. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `function` | Input/Output | A reference to the object used to "invoke according to the standard INVOKE rules and convert to the specified result type"; the referenced object must remain valid for the duration of the call. |
| `arguments` | Input/Output | The list of arguments forwarded to object construction or the function call. |

## Return Value

| Return type | Description |
| --- | --- |
| `Ret` | Returns the result of invoking the function object with the selected arguments. |

## Constraints

- Standard callable objects and member pointer forms are supported.
- invoke_r is an interface provided as a C++23 backport.

## Example

The following Host snippet demonstrates the interface call with concrete objects.

```cpp
#include <asc/std/functional>

decltype(auto) example()
{
    return asc::std::invoke_r<int>([](int value) { return value + 1; }, 3);
}
```

## Related APIs

- [API list for this header](asc_std_functional.md)
