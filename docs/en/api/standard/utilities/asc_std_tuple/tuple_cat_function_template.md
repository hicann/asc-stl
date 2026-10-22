# asc::std::tuple_cat (function template)

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

Header: `<asc/std/tuple>`.

`asc::std::tuple_cat` concatenates the elements of multiple tuples in order.

Standard semantics reference: [cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple).

## Function Prototype

### No-argument overload

```cpp
namespace asc::std {
constexpr tuple<> tuple_cat() noexcept;
} // namespace asc::std
```

### Call-form summary of the concatenation overload

The following is a declaration summary with the internal return-type computation omitted; `auto` is used to illustrate the deduced result and is not a verbatim transcription of the return type spelling in the header. The actual return type is the `asc::std::tuple` obtained by concatenating the element types in input order.

```cpp
namespace asc::std {
template<class... Tuples> constexpr auto tuple_cat(Tuples&&... tuples);
} // namespace asc::std
```

## Parameters

The no-argument overload takes no arguments and returns `tuple<>`.

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Tuples` | The input types to be concatenated; must satisfy the tuple-like protocol supported by the current implementation. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `tuples` | Input/Output | The objects to be concatenated; their elements form the result in argument order; lvalue elements are copied as the corresponding types, and rvalue elements may be moved. |

## Return Value

| Applicable overload | Return type | Description |
| --- | --- | --- |
| No-argument overload | `tuple<>` | Returns an empty tuple. |
| Concatenation overload | `asc::std::tuple<result element types...>` (type description) | Concatenates the element types of each input object in order; the references and cv-qualifiers of the input tuples themselves are not attached to the elements, and reference element types remain references. |

## Constraints

- The inputs must pass the tuple-like type check of the current implementation, and the corresponding `tuple_size`, element types, and `get` access must all be available; merely having similar member names is not sufficient to satisfy the protocol.
- The result elements must be constructible from the corresponding input elements. When the result contains reference elements, the referenced storage must remain valid for the period the result is used.
- The concatenation logic itself requests no dynamic storage; whether element construction allocates memory is determined by the element type. The no-argument overload is `noexcept`, and the concatenation overload has no `noexcept` declaration.

## Example

The following Host example provides concrete inputs and checks the result while the objects are still valid.

```cpp
#include <asc/std/tuple>

bool example()
{
    const auto left = asc::std::make_tuple(1, 2);
    const auto right = asc::std::make_tuple(3);
    const auto joined = asc::std::tuple_cat(left, right);
    return asc::std::get<0>(joined) == 1 && asc::std::get<2>(joined) == 3;
}
```

## Related APIs

- [API list for this header](asc_std_tuple.md)
