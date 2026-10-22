# asc::std::move_sentinel::base

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

`asc::std::move_sentinel::base` returns the underlying iterator or object stored by the adaptor.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

Member of: [`asc::std::move_sentinel`](move_sentinel.md).

```cpp
// Excerpt of the declaration inside asc::std::move_sentinel; template parameters and other members are provided by the enclosing class.
constexpr Sent base() const;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `Sent` | Returns the underlying iterator or object stored by the adaptor. |

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
    return sentinel.base() == values + 2 && iterator != sentinel;
}
```

## Related APIs

- [`asc::std::move_sentinel`](move_sentinel.md)
- [API list for this header](asc_std_iterator.md)
