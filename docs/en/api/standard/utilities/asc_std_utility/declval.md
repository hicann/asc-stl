# asc::std::declval

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

Header: `<asc/std/utility>`.

`asc::std::declval` forms a reference expression of the given type in unevaluated contexts only.

Standard semantics reference: [cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility).

## Function Prototype

```cpp
namespace asc::std {
template<class T> asc::std::add_rvalue_reference_t<T> declval() noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The type for which a hypothetical reference expression is obtained in an unevaluated context; it need not be constructible. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::std::add_rvalue_reference_t<T>` | Forms a reference expression of the given type in unevaluated contexts only. |

## Constraints

- Follows the standard constraints.
- forward_like preserves const/volatile qualification and value category.

## Example

The following snippet demonstrates the call with concrete types; declval is used only in unevaluated type expressions.

```cpp
#include <asc/std/utility>

decltype(auto) example()
{
    using result = decltype(asc::std::declval<int>());
    return sizeof(result);
}
```

## Related APIs

- [API list for this header](asc_std_utility.md)
