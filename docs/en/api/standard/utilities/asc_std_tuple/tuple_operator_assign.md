# asc::std::tuple::`operator=`

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

Header: `<asc/std/tuple>`.

`asc::std::tuple::operator=` updates the object according to the selected assignment overload and returns the prescribed result.

Standard semantics reference: [cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple).

## Function Prototype

Member of: [`asc::std::tuple`](tuple.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside class asc::std::tuple; template parameters and other members are provided by the owning class.
tuple<Types...>& operator=(const tuple<Types...>& other);
```

### Prototype 2

```cpp
// Excerpt of the declaration inside class asc::std::tuple; template parameters and other members are provided by the owning class.
tuple<Types...>& operator=(tuple<Types...>&& other);
```

### Prototype 3

```cpp
// Excerpt of the declaration inside class asc::std::tuple; template parameters and other members are provided by the owning class.
template<class... Other, enable_if_t<sizeof...(Other) == sizeof...(Types), int> = 0> tuple<Types...>& operator=(const tuple<Other...>& other);
```

### Prototype 4

```cpp
// Excerpt of the declaration inside class asc::std::tuple; template parameters and other members are provided by the owning class.
template<class... Other, enable_if_t<sizeof...(Other) == sizeof...(Types), int> = 0> tuple<Types...>& operator=(tuple<Other...>&& other);
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Other` | The element type pack of the element-wise assignment source tuple of Prototypes 3 and 4; the number of elements must be the same as `Types...`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The assignment source tuple: Prototypes 1 and 3 perform element-wise copy assignment from an lvalue reference, and Prototypes 2 and 4 perform element-wise move assignment from an rvalue reference. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototypes 1-4 | `tuple<Types...>&` | Returns a reference to itself after the assignment. |

## Constraints

- The utility itself allocates no additional container storage; element construction, assignment, swapping, or passing into a callable body may still allocate or throw according to their own semantics, so the whole call is not guaranteed to be allocation-free on this basis.

## Example

The following Host snippet demonstrates the call with concrete numeric types; the state and parameters must satisfy the constraints on this page.

```cpp
#include <asc/std/tuple>

void example()
{
    asc::std::tuple<int, int> target(1, 2), source(3, 4);
    target = source;
}
```

## Related APIs

- [`asc::std::tuple`](tuple.md)
- [API list for this header](asc_std_tuple.md)
