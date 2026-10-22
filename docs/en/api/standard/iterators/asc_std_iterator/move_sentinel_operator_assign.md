# asc::std::move_sentinel::`operator=`

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

`asc::std::move_sentinel::operator=` updates the object through the selected assignment overload and returns the specified result.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

Member of: [`move_sentinel`](move_sentinel.md). The following keeps the real participation conditions of the converting assignment; C++17 and the device side select it with SFINAE, and Host C++20 selects it with the same requires condition.

```cpp
template<class S2, enable_if_t<assignable_from<Sent&, const S2&>, int> = 0>
constexpr move_sentinel& operator=(const move_sentinel<S2>& other);
```

Same-type special member assignment follows the C++ implicit declaration rules.

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `S2` | The type of the source sentinel; it must satisfy the conversion condition to the current sentinel type. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source of the converting assignment, with the parameter being a const reference; the stored underlying state must satisfy the conversion and assignment conditions given by the prototype. |

## Return Value

| Return type | Description |
| --- | --- |
| `move_sentinel&` | Updates the target from the underlying end marker stored in the source and returns *this; the source is not changed by this converting assignment. |

## Constraints

- The sentinel type must support the corresponding construction, conversion, or assignment operations and be comparable with the paired underlying iterator.
- The sentinel does not own the underlying range and cannot be dereferenced; its end marker must remain valid during the comparison.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4};
    asc::std::move_sentinel<int*> sentinel(values + 2);
    asc::std::move_iterator<int*> iterator(values);
    asc::std::move_sentinel<const int*> target;
    target = sentinel;
    return target.base() == values + 2;
}
```

## Related APIs

- [`asc::std::move_sentinel`](move_sentinel.md)
- [API list for this header](asc_std_iterator.md)
