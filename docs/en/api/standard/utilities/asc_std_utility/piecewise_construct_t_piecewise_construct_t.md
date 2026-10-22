# asc::std::piecewise_construct_t::piecewise_construct_t

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

`asc::std::piecewise_construct_t::piecewise_construct_t` initializes a `piecewise_construct_t` object with the construction forms listed on this page.

Standard semantics reference: [cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility).

## Function Prototype

### Prototype 1

```cpp
constexpr piecewise_construct_t() noexcept;
```

### Prototype 2

```cpp
constexpr piecewise_construct_t(const piecewise_construct_t& other);
```

### Prototype 3

```cpp
constexpr piecewise_construct_t(piecewise_construct_t&& other);
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source object of the construction; this object is initialized from its corresponding member or underlying state, and the rvalue form may move that state. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source object of the construction; this object is initialized from its corresponding member or underlying state, and the rvalue form may move that state. |

## Return Value

No return value.

## Constraints

- The exception specification follows the corresponding declaration; element operations used on the device side must not throw.
- The direct free comparison entries for pair are `operator==` and `operator<`; the other relational helpers are in `rel_ops`.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/utility>
#include <asc/std/tuple>

bool example()
{
    asc::std::piecewise_construct_t tag{};
    asc::std::pair<int, int> value(tag, asc::std::make_tuple(2), asc::std::make_tuple(3));
    return value.first == 2 && value.second == 3;
}
```

## Related APIs

- [API list for this header](asc_std_utility.md)
