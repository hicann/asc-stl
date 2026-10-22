# asc::std::inplace_vector::inplace_vector

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

Header: `<asc/std/inplace_vector>`.

`asc::std::inplace_vector::inplace_vector` initializes an `inplace_vector` object according to the construction forms listed on this page.

This interface supports both Host and the device side, both limited to the non-throwing operations listed on this page.

Standard semantics reference: [cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector).

## Function Prototype

Member of: [`inplace_vector<T, Capacity>`](inplace_vector.md). The following is the in-class declaration; type aliases and template parameters are provided by the owning class.

### Prototype 1

```cpp
constexpr inplace_vector() noexcept;
```

### Prototype 2

```cpp
constexpr inplace_vector(const inplace_vector& other);
```

### Prototype 3

```cpp
constexpr inplace_vector(inplace_vector&& other);
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source for element-by-element copy construction; the source elements remain unchanged. |

### Parameters of Prototype 3

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source for element-by-element move construction; the source size is unchanged, and the element state is determined by T's move constructor. |

## Return Value

No return value.

## Constraints

- Element storage is inside the container object and is not dynamically allocated; Capacity is the compile-time fixed capacity.
- Both Host and the device side provide the listed non-throwing subset; at, push_back, emplace_back, and resize are not provided.
- The corresponding construction, assignment, and destruction of elements must satisfy the non-throwing usage domain; the constexpr declaration does not guarantee constant evaluation for every T and language mode.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/inplace_vector>

bool example()
{
    asc::std::inplace_vector<int, 4> values;
    if (!values.try_push_back(1)) return false;
    if (!values.try_push_back(3)) return false;
    return values.size() == 2;
}
```

## Related APIs

- [API list for this header](asc_std_inplace_vector.md)
