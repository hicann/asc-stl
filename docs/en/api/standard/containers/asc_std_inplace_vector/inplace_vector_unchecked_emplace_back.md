# asc::std::inplace_vector::unchecked_emplace_back

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

`asc::std::inplace_vector::unchecked_emplace_back` constructs an element in place at the end when the caller guarantees remaining capacity.

This interface supports both Host and the device side, both limited to the non-throwing operations listed on this page.

Standard semantics reference: [cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector).

## Function Prototype

Member of: [`inplace_vector<T, Capacity>`](inplace_vector.md). The following is the in-class declaration; type aliases and template parameters are provided by the owning class.

### Prototype 1

```cpp
template<class... Args>
constexpr reference unchecked_emplace_back(Args&&... args);
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Args` | The pack of argument types for constructing the new element; T must be constructible with the corresponding value categories. |

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `args` | Input | The arguments forwarded to T's constructor; they must be valid during construction, and any borrows held by T must additionally satisfy their lifetimes. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `reference` | Borrows the newly constructed element at the end; the container and that element must remain alive. |

## Constraints

- size() must be less than Capacity before the call; insufficient capacity is not checked.
- Returns a reference to the new element; the element must remain alive for the duration of use of the reference.
- The corresponding construction, assignment, and destruction of elements must satisfy the non-throwing usage domain; the constexpr declaration does not guarantee constant evaluation for every T and language mode.

## Example

The following Host snippet demonstrates the call with a concrete capacity or dimension; the object and indices must satisfy the constraints on this page.

```cpp
#include <asc/std/inplace_vector>
#include <memory>

bool example()
{
    using sequence = asc::std::inplace_vector<int, 8>;
    sequence values;
    values.unchecked_emplace_back(7);
    values.unchecked_emplace_back(9);
    return values.size() == 2 && values[0] == 7 && values[1] == 9;
}
```

## Related APIs

- [`asc::std::inplace_vector`](inplace_vector.md)
- [API list for this header](asc_std_inplace_vector.md)
