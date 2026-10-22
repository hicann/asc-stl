# asc::std::variant::variant

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

Header: `<asc/std/variant>`.

`asc::std::variant::variant` initializes a `variant` object with the construction forms listed on this page.

Standard semantics reference: [cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant).

## Function Prototype

Member of: [`asc::std::variant<Types...>`](variant.md). The following are declarations inside the class; unnamed constraint parameters and the default index are used to select overloads, and the caller does not need to specify them.

### Default construction

```cpp
template <class First = variant_alternative_t<0, variant>, enable_if_t<is_default_constructible_v<First>, int> = 0>
constexpr variant() noexcept(is_nothrow_default_constructible_v<First>);
```

### Copy construction

```cpp
constexpr variant(const variant& other);
```

### Move construction

```cpp
constexpr variant(variant&& other);
```

### Converting value construction

```cpp
template <class T, size_t Index = __variant_best_match<remove_cvref_t<T>, void, Types...>::value,
    enable_if_t<Index != variant_npos && is_constructible_v<variant_alternative_t<Index, variant>, T>, int> = 0>
constexpr variant(T&& value) noexcept(
    is_nothrow_constructible_v<variant_alternative_t<Index, variant>, T>);
```

### In-place construction by index

```cpp
template <size_t Index, class... Args, enable_if_t<(Index < sizeof...(Types)), int> = 0>
constexpr explicit variant(in_place_index_t<Index>, Args&&... args) noexcept(
    is_nothrow_constructible_v<variant_alternative_t<Index, variant>, Args...>);
```

### In-place construction by type

```cpp
template <class T, class... Args, size_t Index = __variant_index_v<T, Types...>,
    enable_if_t<Index != variant_npos && __variant_type_count_v<T, Types...> == 1, int> = 0>
constexpr explicit variant(in_place_type_t<T>, Args&&... args) noexcept(
    is_nothrow_constructible_v<T, Args...>);
```

### Host: initializer list by index

```cpp
template <size_t Index, class Up, class... Args,
    enable_if_t<(Index < sizeof...(Types)) &&
            is_constructible_v<variant_alternative_t<Index, variant>, ::std::initializer_list<Up>&, Args...>,
        int> = 0>
constexpr explicit variant(in_place_index_t<Index>, ::std::initializer_list<Up> list,
    Args&&... args) noexcept(is_nothrow_constructible_v<variant_alternative_t<Index, variant>,
    ::std::initializer_list<Up>&, Args...>);
```

### Host: initializer list by type

```cpp
template <class T, class Up, class... Args, size_t Index = __variant_index_v<T, Types...>,
    enable_if_t<Index != variant_npos && __variant_type_count_v<T, Types...> == 1 &&
            is_constructible_v<T, ::std::initializer_list<Up>&, Args...>,
        int> = 0>
constexpr explicit variant(in_place_type_t<T>, ::std::initializer_list<Up> list,
    Args&&... args) noexcept(is_nothrow_constructible_v<T, ::std::initializer_list<Up>&, Args...>);
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Types` | The list of alternative types of the owning `variant`; it must not contain arrays, references, or `void`. |
| `T` | The alternative type selected for in-place construction by type; it must occur exactly once. |
| `Index` | The alternative position for construction by index, starting from 0 and less than the number of alternative types; in the forms selected by type or value it is deduced by the implementation. |
| `Args` | The parameter types forwarded to the selected alternative type's constructor. |
| `Up` | The element type of the Host initializer list. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input; Input/Output when swapping | A same-type source object; the rvalue form may move its active alternative value, and a swap changes both objects. |
| `value` | Input (may be moved) | The value used to select and construct or assign the active alternative. |
| `args` | Input (may be moved) | Arguments forwarded to the selected type's constructor. |
| `list` | Input | The initializer list provided by the Host-only forms; used together with the remaining arguments for construction. |

## Return Value

No return value.

## Constraints

- The object holds one active alternative value at a time; the selected alternative must be confirmed through `index()` before reading.
- Alternative types used on the device and their construction, assignment, destruction, and swap operations must be available in the corresponding programming mode and must not throw.
- The by-index form requires the index to be in range; the by-type form requires the type to occur exactly once in the alternative list. The selected type must be constructible from the given arguments.
- The overloads taking `::std::initializer_list` may be called on the Host only.
- Default construction requires the first alternative type to be default constructible and activates index 0. Converting value construction requires a selectable and constructible alternative type to exist.

## Example

The following Host example uses a concrete object and checks the result of the call.

```cpp
#include <asc/std/variant>

bool example()
{
    asc::std::variant<int, float> zero;
    asc::std::variant<int, float> selected(asc::std::in_place_index<1>, 2.5F);
    const auto copied = selected;
    return zero.index() == 0 && asc::std::get<0>(zero) == 0 &&
        copied.index() == 1 && asc::std::get<1>(copied) == 2.5F;
}
```

## Related APIs

- [API list for this header](asc_std_variant.md)
