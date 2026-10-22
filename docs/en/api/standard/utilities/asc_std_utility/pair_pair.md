# asc::std::pair::pair

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

`asc::std::pair::pair` initializes a `pair` object with the construction forms listed on this page.

Standard semantics reference: [cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility).

## Function Prototype

The following is a **call-form summary** inside class `pair<T1, T2>`, omitting the implementation selectors. Each form participates only when the corresponding elements are constructible or assignable; whether default/value construction is explicit is layered by the elements' implicit conversion capabilities, and the summary must not be merged into unconditional overload definitions.

```cpp
template<class U1 = T1, class U2 = T2> constexpr pair() noexcept(is_nothrow_default_constructible_v<T1>&& is_nothrow_default_constructible_v<T2>);
```

```cpp
template<class U1 = T1, class U2 = T2> explicit constexpr pair() noexcept(is_nothrow_default_constructible_v<T1>&& is_nothrow_default_constructible_v<T2>);
```

```cpp
pair(const pair& other) = default;
```

```cpp
pair(pair&& other) = default;
```

```cpp
template<class U1 = T1, class U2 = T2> constexpr pair(U1&& left, U2&& right) noexcept(is_nothrow_constructible_v<T1, U1&&>&& is_nothrow_constructible_v<T2, U2&&>);
```

```cpp
template<class U1, class U2> explicit constexpr pair(U1&& left, U2&& right) noexcept(is_nothrow_constructible_v<T1, U1&&>&& is_nothrow_constructible_v<T2, U2&&>);
```

```cpp
template<class U1, class U2> constexpr pair(pair<U1, U2>& other) noexcept(is_nothrow_constructible_v<T1, U1&>&& is_nothrow_constructible_v<T2, U2&>);
```

```cpp
template<class U1, class U2> constexpr pair(const pair<U1, U2>&& other) noexcept(is_nothrow_constructible_v<T1, const U1&&>&& is_nothrow_constructible_v<T2, const U2&&>);
```

```cpp
template<class PairLike> constexpr pair(PairLike&& other);
```

```cpp
template<class U1, class U2> constexpr pair(const pair<U1, U2>& other) noexcept(is_nothrow_constructible_v<T1, const U1&>&& is_nothrow_constructible_v<T2, const U2&>);
```

```cpp
template<class U1, class U2> constexpr pair(pair<U1, U2>&& other) noexcept(is_nothrow_constructible_v<T1, U1&&>&& is_nothrow_constructible_v<T2, U2&&>);
```

```cpp
template<class... Args1, class... Args2> constexpr pair(piecewise_construct_t, tuple<Args1...> left, tuple<Args2...> right) noexcept(is_nothrow_constructible_v<T1, Args1...>&& is_nothrow_constructible_v<T2, Args2...>);
```

## Parameters

The selection parameters omitted from the summary have been turned into the public participation conditions on this page; the caller invokes with ordinary arguments.

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `U1` | The type of the construction source for first; it defaults to T1 and may be deduced from the forwarding reference in an actual call. |
| `U2` | The type of the construction source for second; it defaults to T2 and may be deduced from the forwarding reference in an actual call. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `U1` | The type of the construction source for first; it defaults to T1 and may be deduced from the forwarding reference in an actual call. |
| `U2` | The type of the construction source for second; it defaults to T2 and may be deduced from the forwarding reference in an actual call. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source object of the construction; this object is initialized from its corresponding member or underlying state, and the rvalue form may move that state. |

### Parameters of Prototype 4

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | The source object of the construction; this object is initialized from its corresponding member or underlying state, and the rvalue form may move that state. |

### Parameters of Prototype 5

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `U1` | The type of the source pair's first element or of the first construction argument. |
| `U2` | The type of the source pair's second element or of the second construction argument. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input/Output | The value used to initialize the first element; the referenced object must remain valid during the call. |
| `right` | Input/Output | The value used to initialize the second element; the referenced object must remain valid during the call. |

### Parameters of Prototype 6

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `U1` | The type of the source pair's first element or of the first construction argument. |
| `U2` | The type of the source pair's second element or of the second construction argument. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input/Output | The value used to initialize the first element; the referenced object must remain valid during the call. |
| `right` | Input/Output | The value used to initialize the second element; the referenced object must remain valid during the call. |

### Parameters of Prototype 7

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `U1` | The type of the source pair's first element or of the first construction argument. |
| `U2` | The type of the source pair's second element or of the second construction argument. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | The source object of the construction; this object is initialized from its corresponding member or underlying state, and the rvalue form may move that state. |

### Parameters of Prototype 8

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `U1` | The type of the source pair's first element or of the first construction argument. |
| `U2` | The type of the source pair's second element or of the second construction argument. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source object of the construction; this object is initialized from its corresponding member or underlying state, and the rvalue form may move that state. |

### Parameters of Prototype 9

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `PairLike` | A pair-like type providing two elements with corresponding get access; both elements must be usable for the corresponding construction or assignment. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | The source object of the construction; this object is initialized from its corresponding member or underlying state, and the rvalue form may move that state. |

### Parameters of Prototype 10

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `U1` | The type of the source pair's first element or of the first construction argument. |
| `U2` | The type of the source pair's second element or of the second construction argument. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source object of the construction; this object is initialized from its corresponding member or underlying state, and the rvalue form may move that state. |

### Parameters of Prototype 11

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `U1` | The type of the source pair's first element or of the first construction argument. |
| `U2` | The type of the source pair's second element or of the second construction argument. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | The source object of the construction; this object is initialized from its corresponding member or underlying state, and the rvalue form may move that state. |

### Parameters of Prototype 12

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Args1` | The list of argument types forwarded to the construction of the first element. |
| `Args2` | The list of argument types forwarded to the construction of the second element. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The tuple of arguments forwarded to the construction of the first element. |
| `right` | Input | The tuple of arguments forwarded to the construction of the second element. |

## Return Value

No return value.

## Constraints

- The pair-like form omits the computed noexcept expression: the construction does not throw when both the retrieval and the construction of the corresponding elements do not throw; the exception specifications of the other forms are shown in the summary prototypes.

- Default construction requires both elements to be default constructible; the implicit form is used when both are implicitly default constructible, otherwise the explicit one. Two-value construction requires element-by-element constructibility, and it carries no explicit when both sources are implicitly convertible. The pair-like form requires two elements accessible through get and a source that is not a pair specialization; piecewise_construct applies the two groups of tuple arguments to first and second respectively.

- The exception specification follows the corresponding declaration; element operations used on the device side must not throw.
- The direct free comparison entries for pair are `operator==` and `operator<`; the other relational helpers are in `rel_ops`.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/utility>
#include <asc/std/tuple>

bool example()
{
    asc::std::pair<int, int> zero;
    asc::std::pair<int, int> values(2, 4);
    auto copy = values;
    auto moved = asc::std::move(copy);
    asc::std::pair<int, int> piecewise(asc::std::piecewise_construct,
        asc::std::make_tuple(3), asc::std::make_tuple(5));
    return zero.first == 0 && moved.first == 2 && moved.second == 4 && piecewise.first == 3 && piecewise.second == 5;
}
```

## Related APIs

- [API list for this header](asc_std_utility.md)
