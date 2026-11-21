# asc::std::variant::emplace

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

`asc::std::variant::emplace` directly constructs the element in place.

Standard semantics reference: [cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant).

## Function Prototype

Member of: [`asc::std::variant<Types...>`](variant.md). The following are declarations inside the class; unnamed constraint parameters and the default index are used to select overloads, and the caller does not need to specify them.

### Construction by index

```cpp
template <size_t Index, class... Args>
constexpr variant_alternative_t<Index, variant>& emplace(Args&&... args);
```

### Construction by type

```cpp
template <class T, class... Args, size_t Index = __variant_index_v<T, Types...>,
    enable_if_t<Index != variant_npos && __variant_type_count_v<T, Types...> == 1, int> = 0>
constexpr T& emplace(Args&&... args);
```

### Host: initializer list by index

```cpp
template <size_t Index, class Up, class... Args,
    enable_if_t<(Index < sizeof...(Types)) &&
            is_constructible_v<variant_alternative_t<Index, variant>, ::std::initializer_list<Up>&, Args...>,
        int> = 0>
constexpr variant_alternative_t<Index, variant>& emplace(
    ::std::initializer_list<Up> list, Args&&... args);
```

### Host: initializer list by type

```cpp
template <class T, class Up, class... Args, size_t Index = __variant_index_v<T, Types...>,
    enable_if_t<Index != variant_npos && __variant_type_count_v<T, Types...> == 1 &&
            is_constructible_v<T, ::std::initializer_list<Up>&, Args...>,
        int> = 0>
constexpr T& emplace(::std::initializer_list<Up> list, Args&&... args);
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
| `args` | Input (may be moved) | Arguments forwarded to the selected type's constructor. |
| `list` | Input | The initializer list provided by the Host-only forms; used together with the remaining arguments for construction. |

## Return Value

Returns a reference to the newly constructed alternative object; `T&` for the by-type form and `variant_alternative_t<Index, variant>&` for the by-index form. The reference is valid until that alternative object is replaced or destroyed or the owning `variant` is destroyed; do not return a reference to an element of a local `variant`.

## Constraints

- On Host, `emplace` destroys the old value before constructing the new one. If construction throws, `index()` returns `variant_npos` and `valueless_by_exception()` returns `true`. A later successful `emplace` or assignment restores an active value.
- The new active index is published only after successful construction; on failure the old alternative value is not preserved.

- The object holds one active alternative value at a time; the selected alternative must be confirmed through `index()` before reading.
- Alternative types used on the device and their construction, assignment, destruction, and swap operations must be available in the corresponding programming mode and must not throw.
- The by-index form requires the index to be in range; the by-type form requires the type to occur exactly once in the alternative list. The selected type must be constructible from the given arguments.
- The overloads taking `::std::initializer_list` may be called on the Host only.

## Example

The following Host example uses a concrete object and checks the result of the call.

```cpp
#include <asc/std/variant>

bool example()
{
    asc::std::variant<int, float> value(7);
    auto& result = value.emplace<float>(2.5F);
    return value.index() == 1 && &result == &asc::std::get<1>(value) && result == 2.5F;
}
```

## Related APIs

- [`asc::std::variant`](variant.md)
- [API list for this header](asc_std_variant.md)
