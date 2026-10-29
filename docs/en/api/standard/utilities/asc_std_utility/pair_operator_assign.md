# asc::std::pair::`operator=`

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

Header: `<asc/std/utility>`.

`asc::std::pair::operator=` updates the object with the selected assignment overload and returns the specified result.

Standard semantics reference: [cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility).

## Function Prototype

The following is a **call-form summary** inside class `pair<T1, T2>`, omitting the implementation selectors. Each form participates only when the corresponding elements are constructible or assignable; whether default/value construction is explicit is layered by the elements' implicit conversion capabilities, and the summary must not be merged into unconditional overload definitions.

```cpp
pair<T1, T2>& operator=(const pair<T1, T2>& other) = default;
```

```cpp
pair<T1, T2>& operator=(pair<T1, T2>&& other) = default;
```

```cpp
template<class U1, class U2> constexpr pair<T1, T2>& operator=(pair<U1, U2>&& other) noexcept(is_nothrow_assignable_v<T1&, U1>&& is_nothrow_assignable_v<T2&, U2>);
```

```cpp
template<class U1, class U2> constexpr pair<T1, T2>& operator=(const pair<U1, U2>& other) noexcept(is_nothrow_assignable_v<T1&, const U1&>&& is_nothrow_assignable_v<T2&, const U2&>);
```

```cpp
template<class U1, class U2> constexpr const pair<T1, T2>& operator=(pair<U1, U2>&& other) const noexcept(is_nothrow_assignable_v<const T1&, U1>&& is_nothrow_assignable_v<const T2&, U2>);
```

```cpp
template<class U1, class U2> constexpr const pair<T1, T2>& operator=(const pair<U1, U2>& other) const noexcept(is_nothrow_assignable_v<const T1&, const U1&>&& is_nothrow_assignable_v<const T2&, const U2&>);
```

```cpp
template<class PairLike> constexpr pair<T1, T2>& operator=(PairLike&& other);
```

## Parameters

The selection parameters omitted from the summary have been turned into the public participation conditions on this page; the caller invokes with ordinary arguments.

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source object of the assignment; the lvalue form copies its state, and the rvalue form transfers state through the corresponding members' move operations. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | The source object of the assignment; the lvalue form copies its state, and the rvalue form transfers state through the corresponding members' move operations. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `U1` | The type of the source pair's first element or of the first construction argument. |
| `U2` | The type of the source pair's second element or of the second construction argument. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | The source object of the assignment; the lvalue form copies its state, and the rvalue form transfers state through the corresponding members' move operations. |

### Parameters of Prototype 4

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `U1` | The type of the source pair's first element or of the first construction argument. |
| `U2` | The type of the source pair's second element or of the second construction argument. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source object of the assignment; the lvalue form copies its state, and the rvalue form transfers state through the corresponding members' move operations. |

### Parameters of Prototype 5

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `U1` | The type of the source pair's first element or of the first construction argument. |
| `U2` | The type of the source pair's second element or of the second construction argument. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | The source object of the assignment; the lvalue form copies its state, and the rvalue form transfers state through the corresponding members' move operations. |

### Parameters of Prototype 6

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `U1` | The type of the source pair's first element or of the first construction argument. |
| `U2` | The type of the source pair's second element or of the second construction argument. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source object of the assignment; the lvalue form copies its state, and the rvalue form transfers state through the corresponding members' move operations. |

### Parameters of Prototype 7

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `PairLike` | A pair-like type providing two elements with corresponding get access; both elements must be usable for the corresponding construction or assignment. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | The source object of the assignment; the lvalue form copies its state, and the rvalue form transfers state through the corresponding members' move operations. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `pair<T1, T2> &` | Returns a reference to the updated current object, which can continue to be assigned or used in compound operations. |
| Prototype 2 | `pair<T1, T2> &` | Returns a reference to the updated current object, which can continue to be assigned or used in compound operations. |
| Prototype 3 | `pair<T1, T2> &` | Returns a reference to the updated current object, which can continue to be assigned or used in compound operations. |
| Prototype 4 | `pair<T1, T2> &` | Returns a reference to the updated current object, which can continue to be assigned or used in compound operations. |
| Prototype 5 | `const pair<T1, T2> &` | Returns a reference to the updated current object, which can continue to be assigned or used in compound operations. |
| Prototype 6 | `const pair<T1, T2> &` | Returns a reference to the updated current object, which can continue to be assigned or used in compound operations. |
| Prototype 7 | `pair<T1, T2> &` | Returns a reference to the updated current object, which can continue to be assigned or used in compound operations. |

## Constraints

- Cross-type assignment requires each of the two target elements to be assignable from the corresponding source; the const-member forms additionally require the const element expressions to be assignable. A generic pair-like source must have two elements accessible through get and must not be a pair specialization; assignment to reference elements acts on the referenced object.

- The exception specification follows the corresponding declaration; element operations used on the device side must not throw.
- The direct free comparison entries for pair are `operator==` and `operator<`; the other relational helpers are in `rel_ops`.

## Example

The following Host snippet demonstrates the call with concrete types; input ranges and objects must remain valid during use.

```cpp
#include <asc/std/utility>

bool example()
{
    asc::std::pair<int, int> left(1, 2), right(3, 4);
    left = right;
    return left.first == 3 && left.second == 4;
}
```

## Related APIs

- [`asc::std::pair`](pair.md)
- [API list for this header](asc_std_utility.md)
