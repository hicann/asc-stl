# asc::std::move_sentinel::move_sentinel

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

`asc::std::move_sentinel::move_sentinel` initializes a `move_sentinel` object with the constructor forms listed on this page.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

Member of: [`move_sentinel<Sent>`](move_sentinel.md). The following is the selection form used by C++17 and the device side; Host C++20 uses the same convertible_to condition for the converting constructor.

### Prototype 1

```cpp
constexpr move_sentinel() = default;
```

### Prototype 2

```cpp
constexpr explicit move_sentinel(Sent sentinel);
```

### Prototype 3

```cpp
template<class S2, enable_if_t<convertible_to<const S2&, Sent>, int> = 0>
constexpr move_sentinel(const move_sentinel<S2>& other);
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `sentinel` | Input | The wrapped sentinel; the new object stores a copy of it, used for comparison with a move_iterator to determine the end of the range. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `S2` | The sentinel type of the source move_sentinel; const S2& must satisfy convertible_to<const S2&, Sent>, including the implicit conversion requirements. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The copy source move_sentinel; the new object stores a copy of its sentinel. |

## Return Value

No return value.

## Constraints

- The sentinel type must support the corresponding construction, conversion, or assignment operations and be comparable with the paired underlying iterator.
- The sentinel does not own the underlying range and cannot be dereferenced; its end marker must remain valid during the comparison.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>
#include <asc/std/type_traits>

bool example()
{
    int values[] = {2, 4};
    asc::std::move_sentinel<int*> empty;
    asc::std::move_sentinel<int*> direct(values + 2);
    asc::std::move_sentinel<const int*> converted(direct);
    static_assert(!asc::std::is_convertible_v<int*, asc::std::move_sentinel<int*>>);
    return empty.base() == nullptr && converted.base() == values + 2;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
