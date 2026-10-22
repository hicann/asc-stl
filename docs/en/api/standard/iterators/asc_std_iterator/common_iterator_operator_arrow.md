# asc::std::common_iterator::`operator-`>

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

`asc::std::common_iterator::operator->` returns a pointer that can be used to access members of the pointed-to object.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

Member of: [`asc::std::common_iterator`](common_iterator.md).

```cpp
// Excerpt of the declaration inside common_iterator; the class template parameters and the remaining members are provided by the enclosing class.
// C++17 and Device selection form; Host C++20 expresses the same condition with requires.
template<class I2 = Iter,
    enable_if_t<indirectly_readable<const I2> &&
        (__common_iterator_detail::__ci_has_const_arrow<I2> ||
         is_reference_v<iter_reference_t<I2>> ||
         constructible_from<iter_value_t<I2>, iter_reference_t<I2>>), int> = 0>
constexpr decltype(auto) operator->() const;
```

The auxiliary test in the definition excerpt checks whether the underlying const iterator can directly provide arrow access; the other branches obtain the address from the reference or construct a value proxy.

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `I2` | The member selection type, defaulting to the enclosing class's `Iter`; it must satisfy the expression or traversal requirements of this prototype. |

## Return Value

| Return type | Description |
| --- | --- |
| `decltype(auto)` | Returns a pointer through which members of the currently pointed-to object can be accessed. |

## Constraints

- `Iter` and `Sent` are distinct types and must satisfy the pairing requirements of input/output iterators and sentinels; the adaptor stores one of the two states.
- Dereference, arrow access, and increment can only act on an object that currently holds an iterator for which the operation is valid, not on the sentinel state.
- The adaptor does not own the underlying range; the pointed-to objects must remain valid during access.
- The underlying const iterator must be indirectly readable and must provide member access through its own arrow, the reference obtained by dereference, or a constructible value proxy.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4, 6};
    using It = asc::std::counted_iterator<int*>;
    using Common = asc::std::common_iterator<It, asc::std::default_sentinel_t>;
    Common iterator(It(values, 3));
    auto pointer = iterator.operator->();
    return *pointer == 2;
}
```

## Related APIs

- [`asc::std::common_iterator`](common_iterator.md)
- [API list for this header](asc_std_iterator.md)
