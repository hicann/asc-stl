# asc::std::ranges::subrange::subrange

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

Header: `<asc/std/ranges>`.

`asc::std::ranges::subrange::subrange` initializes a `subrange` object according to the construction forms listed on this page.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

### Prototype 1

```cpp
subrange();
```

### Prototype 2

```cpp
template<class It> constexpr subrange(It first, Sent sentinel);
```

### Prototype 3

```cpp
template<class It> constexpr subrange(It first, Sent sentinel, make_unsigned_t<iter_difference_t<Iter>> last);
```

### Prototype 4

```cpp
template<class Range> constexpr subrange(Range&& base);
```

### Prototype 5

```cpp
template<class Range> constexpr subrange(Range&& base, make_unsigned_t<iter_difference_t<Iter>> first);
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `It` | The iterator type used by the subrange, which must satisfy the input iterator requirements. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The starting iterator or pointer of the subrange. |
| `sentinel` | Input | The past-the-end sentinel of the subrange, paired with first to delimit the range. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `It` | The iterator type used by the subrange, which must satisfy the input iterator requirements. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The starting iterator or pointer of the subrange. |
| `sentinel` | Input | The past-the-end sentinel of the subrange, paired with first to delimit the range. |
| `last` | Input | The number of elements in the range, of the unsigned version of the iterator difference type; it must match the actual length and lets size() avoid traversal. |

### Parameters of Prototype 4

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Range` | The type of the input range or view; it must satisfy the traversal requirements of the selected prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `base` | Input/Output | The underlying range or view being sliced; views are wrapped by value, and lvalue containers are sliced by their first and last iterators. |

### Parameters of Prototype 5

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Range` | The type of the input range or view; it must satisfy the traversal requirements of the selected prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `base` | Input/Output | The underlying range or view being sliced; views are wrapped by value, and lvalue containers are sliced by their first and last iterators. |
| `first` | Input | The number of elements in the range, of the unsigned version of the iterator difference type; it must match the actual length of the base range and lets size() avoid traversal. |

## Return Value

No return value.

## Constraints

- Element access and iteration of the view do not allocate additional storage; the lifetime of the underlying range must cover all uses of the borrowing views.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/ranges>
#include <asc/std/array>
#include <asc/std/iterator>
#include <asc/std/tuple>

bool example()
{
    int values[] = {1, 2, 3, 4};
    using Base = asc::std::ranges::subrange<int*>;
    Base base(values, values + 4);
    Base view(values, values + 4);
    return *view.begin() == 1;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
