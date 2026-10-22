# asc::std::bind

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

`asc::std::bind` binds a function object with some of its arguments into a new callable object.

Standard semantics reference: [cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional).

## Function Prototype

The following is a summary of the call forms; the concrete implementation type of the returned object is not a public type the caller needs to name.

```cpp
namespace asc::std {
template<class Fp, class... BoundArgs>
constexpr auto bind(Fp&& f, BoundArgs&&... bound_args);
}
```

```cpp
namespace asc::std {
template<class Rp, class Fp, class... BoundArgs>
constexpr auto bind(Fp&& f, BoundArgs&&... bound_args);
}
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Fp` | The function object type to be stored or invoked; the actual call must accept the corresponding arguments. |
| `BoundArgs` | The list of argument types stored at bind time; placeholders are replaced by the arguments at the corresponding positions at call time. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `f` | Input/Output | A reference to the object used by "bind a function object with some of its arguments into a new callable object"; the referenced object must remain valid for the duration of the call. |
| `bound_args` | Input/Output | The list of arguments forwarded to object construction or the function call. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rp` | The explicitly specified return type of the bound call; the result of invoking the bound function must be returnable as this type. |
| `Fp` | The function object type to be stored or invoked; the actual call must accept the corresponding arguments. |
| `BoundArgs` | The list of argument types stored at bind time; placeholders are replaced by the arguments at the corresponding positions at call time. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `f` | Input/Output | A reference to the object used by "bind a function object with some of its arguments into a new callable object"; the referenced object must remain valid for the duration of the call. |
| `bound_args` | Input/Output | The list of arguments forwarded to object construction or the function call. |

## Return Value

Returns a callable object whose concrete implementation type is determined by the header. The default form deduces the target call result; the form that specifies Rp converts the call result to Rp. The bound object stores the decayed callable target and the bound arguments; reference_wrapper arguments still borrow the original objects.

## Constraints

- Standard callable objects and member pointer forms are supported.

## Example

The following Host example demonstrates this interface with concrete inputs and a checkable result.

```cpp
#include <asc/std/functional>

bool example()
{
    auto bound = asc::std::bind(asc::std::plus<int>{}, asc::std::placeholders::_1, 2);
    return bound(3) == 5;
}
```

## Related APIs

- [API list for this header](asc_std_functional.md)
