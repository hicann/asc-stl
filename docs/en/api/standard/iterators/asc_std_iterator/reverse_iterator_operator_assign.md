# asc::std::reverse_iterator::`operator=`

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

Header: `<asc/std/iterator>`.

`asc::std::reverse_iterator::operator=` updates the object through the selected assignment overload and returns the specified result.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

Member of: [`reverse_iterator`](reverse_iterator.md). The following keeps the real participation conditions of the converting assignment; this SFINAE form applies in both language modes.

```cpp
template<class U, enable_if_t<!is_same_v<U, Iter> && is_convertible_v<const U&, Iter>
    && is_assignable_v<Iter&, const U&>, int> = 0>
constexpr reverse_iterator& operator=(const reverse_iterator<U>& other) noexcept(is_nothrow_assignable_v<Iter&, const U&>);
```

Same-type special member assignment follows the C++ implicit declaration rules.

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `U` | The source iterator type; it must satisfy the conversion or assignment condition of the current adaptor. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source of the converting assignment, with the parameter being a const reference; the stored underlying state must satisfy the conversion and assignment conditions given by the prototype. |

## Return Value

| Return type | Description |
| --- | --- |
| `reverse_iterator&` | Updates the target from the reversed base position stored in the source and returns *this; the source remains valid. |

## Constraints

- The underlying iterator must support bidirectional traversal; random-access members additionally require the underlying iterator to support the corresponding offset or subscript operations.
- The reverse iterator accesses the element before `base()`; dereference or arrow access requires that previous position to be valid.
- The adaptor does not own the underlying range; the lifetime of returned references or pointers is bound by the underlying object.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4, 6, 8};
    asc::std::reverse_iterator<int*> iterator(values + 4);
    asc::std::reverse_iterator<const int*> target;
    target = iterator;
    return *target == 8;
}
```

## Related APIs

- [`asc::std::reverse_iterator`](reverse_iterator.md)
- [API list for this header](asc_std_iterator.md)
