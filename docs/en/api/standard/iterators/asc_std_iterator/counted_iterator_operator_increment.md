# asc::std::counted_iterator::`operator++`

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

`asc::std::counted_iterator::operator++` advances the current iterator or count by one step.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

Member of: [`asc::std::counted_iterator`](counted_iterator.md).

```cpp
// Excerpt of the declaration inside counted_iterator; the class template parameters and the remaining members are provided by the enclosing class.
constexpr counted_iterator& operator++();
```

The postfix increment has only one member template; the following two conditional branches are mutually exclusive:

```cpp
// Excerpt of the declaration inside counted_iterator.
#if CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() && !CANN_ASC_STL_DETAIL_HAS_CXX20()
template<class I2 = Iter>
auto operator++(int);
#else
template<class I2 = Iter>
constexpr auto operator++(int);
#endif
```

## Parameters

The prefix form takes no parameters. In the postfix form, the `int` is a placeholder parameter that distinguishes the syntax, usually written as `iterator++`.

| Parameter | Description |
| --- | --- |
| `I2` | The selection type for the postfix form, defaulting to the enclosing class's `Iter`; it is usually provided by the default value. |

## Return Value

The prefix form returns a reference to the current adaptor after the increment. The postfix form returns a copy of the `counted_iterator` from before the increment when the underlying type satisfies the forward iterator requirements; otherwise it returns the result of the underlying `current_++`, whose type is determined by the underlying iterator.

After success, both forms move the current position forward by one and decrease the remaining count by 1. The non-forward branch with exception support restores the original count if the underlying postfix increment throws an exception.

## Constraints

- `Iter` must satisfy the traversal capabilities required by this operation; the adaptor does not own the underlying range.
- `count()` gives the number of elements remaining from the current position; dereference and increment require the remaining count to be greater than 0.
- The underlying position after the shift and the corresponding count must be valid and must not go beyond the actually valid range.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4, 6, 8};
    asc::std::counted_iterator<int*> iterator(values, 4);
    auto old = iterator++;
    return *old == 2 && *iterator == 4;
}
```

## Related APIs

- [`asc::std::counted_iterator`](counted_iterator.md)
- [API list for this header](asc_std_iterator.md)
