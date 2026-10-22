# asc::std::get

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

Headers: `<asc/std/array>`, `<asc/std/tuple>`, `<asc/std/utility>`, `<asc/std/variant>`.

`asc::std::get` accesses, by compile-time index, the elements of `array`, `tuple`, and `pair`, as well as the real or imaginary part of the `complex<float>` exported by `<asc/std/tuple>`; `tuple` and `pair` can also be accessed by type. It returns a reference to the element in the original object, with cv-qualification and value category propagated from the argument; the referenced object must remain alive. `variant` additionally provides the 8 `get` overloads listed on this page, which access the currently active alternative; their mismatch failure path directly triggers a trap. When a match needs to be checked first, `get_if` can be used.

Standard semantics reference: [cppreference `array`](https://en.cppreference.com/w/cpp/header/array).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class T1, class ...Args> constexpr T1&& get(tuple<Args...>&& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/tuple>`.

### Prototype 2

```cpp
namespace asc::std {
template<class T1, class ...Args> constexpr T1& get(tuple<Args...>& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/tuple>`.

### Prototype 3

```cpp
namespace asc::std {
template<class T1, class ...Args> constexpr const T1&& get(const tuple<Args...>&& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/tuple>`.

### Prototype 4

```cpp
namespace asc::std {
template<class T1, class ...Args> constexpr const T1& get(const tuple<Args...>& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/tuple>`.

### Prototype 5

```cpp
namespace asc::std {
template<class T1, class T2> constexpr T1&& get(pair<T1, T2>&& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/utility>`.

### Prototype 6

```cpp
namespace asc::std {
template<class T1, class T2> constexpr T1&& get(pair<T2, T1>&& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/utility>`.

### Prototype 7

```cpp
namespace asc::std {
template<class T1, class T2> constexpr T1& get(pair<T1, T2>& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/utility>`.

### Prototype 8

```cpp
namespace asc::std {
template<class T1, class T2> constexpr T1& get(pair<T2, T1>& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/utility>`.

### Prototype 9

```cpp
namespace asc::std {
template<class T1, class T2> constexpr const T1&& get(const pair<T1, T2>&& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/utility>`.

### Prototype 10

```cpp
namespace asc::std {
template<class T1, class T2> constexpr const T1&& get(const pair<T2, T1>&& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/utility>`.

### Prototype 11

```cpp
namespace asc::std {
template<class T1, class T2> constexpr const T1& get(const pair<T1, T2>& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/utility>`.

### Prototype 12

```cpp
namespace asc::std {
template<class T1, class T2> constexpr const T1& get(const pair<T2, T1>& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/utility>`.

### Prototype 13

```cpp
namespace asc::std {
template<size_t Index, class T> [[nodiscard]] constexpr T&& get(complex<T>&& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/tuple>`.

### Prototype 14

```cpp
namespace asc::std {
template<size_t Index, class T> [[nodiscard]] constexpr T& get(complex<T>& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/tuple>`.

### Prototype 15

```cpp
namespace asc::std {
template<size_t Index, class T> [[nodiscard]] constexpr const T&& get(const complex<T>&& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/tuple>`.

### Prototype 16

```cpp
namespace asc::std {
template<size_t Index, class T> [[nodiscard]] constexpr const T& get(const complex<T>& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/tuple>`.

### Prototype 17

```cpp
namespace asc::std {
template<size_t Index, class ...T> constexpr const tuple_element_t<Index, tuple<T...>>&& get(const tuple<T...>&& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/tuple>`.

### Prototype 18

```cpp
namespace asc::std {
template<size_t Index, class ...T> constexpr const tuple_element_t<Index, tuple<T...>>& get(const tuple<T...>& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/tuple>`.

### Prototype 19

```cpp
namespace asc::std {
template<size_t Index, class ...T> constexpr tuple_element_t<Index, tuple<T...>>&& get(tuple<T...>&& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/tuple>`.

### Prototype 20

```cpp
namespace asc::std {
template<size_t Index, class ...T> constexpr tuple_element_t<Index, tuple<T...>>& get(tuple<T...>& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/tuple>`.

### Prototype 21

```cpp
namespace asc::std {
template<size_t Index, class T1, class T2> constexpr const tuple_element_t<Index, pair<T1, T2>>&& get(const pair<T1, T2>&& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/utility>`.

### Prototype 22

```cpp
namespace asc::std {
template<size_t Index, class T1, class T2> constexpr const tuple_element_t<Index, pair<T1, T2>>& get(const pair<T1, T2>& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/utility>`.

### Prototype 23

```cpp
namespace asc::std {
template<size_t Index, class T1, class T2> constexpr tuple_element_t<Index, pair<T1, T2>>&& get(pair<T1, T2>&& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/utility>`.

### Prototype 24

```cpp
namespace asc::std {
template<size_t Index, class T1, class T2> constexpr tuple_element_t<Index, pair<T1, T2>>& get(pair<T1, T2>& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/utility>`.

### Prototype 25

```cpp
namespace asc::std {
template<size_t Index, class T, size_t Size> constexpr T&& get(array<T, Size>&& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/array>`.

### Prototype 26

```cpp
namespace asc::std {
template<size_t Index, class T, size_t Size> constexpr T& get(array<T, Size>& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/array>`.

### Prototype 27

```cpp
namespace asc::std {
template<size_t Index, class T, size_t Size> constexpr const T&& get(const array<T, Size>&& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/array>`.

### Prototype 28

```cpp
namespace asc::std {
template<size_t Index, class T, size_t Size> constexpr const T& get(const array<T, Size>& value) noexcept;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/array>`.

### Prototype 29

```cpp
namespace asc::std {
template<size_t Index, class... Types>
constexpr decltype(auto) get(variant<Types...>& value);
}
```

This prototype corresponds to the common header: `<asc/std/variant>`.

### Prototype 30

```cpp
namespace asc::std {
template<size_t Index, class... Types>
constexpr decltype(auto) get(const variant<Types...>& value);
}
```

This prototype corresponds to the common header: `<asc/std/variant>`.

### Prototype 31

```cpp
namespace asc::std {
template<size_t Index, class... Types>
constexpr decltype(auto) get(variant<Types...>&& value);
}
```

This prototype corresponds to the common header: `<asc/std/variant>`.

### Prototype 32

```cpp
namespace asc::std {
template<size_t Index, class... Types>
constexpr decltype(auto) get(const variant<Types...>&& value);
}
```

This prototype corresponds to the common header: `<asc/std/variant>`.

### Prototype 33

```cpp
namespace asc::std {
template<class T, class... Types>
constexpr decltype(auto) get(variant<Types...>& value);
}
```

This prototype corresponds to the common header: `<asc/std/variant>`.

### Prototype 34

```cpp
namespace asc::std {
template<class T, class... Types>
constexpr decltype(auto) get(const variant<Types...>& value);
}
```

This prototype corresponds to the common header: `<asc/std/variant>`.

### Prototype 35

```cpp
namespace asc::std {
template<class T, class... Types>
constexpr decltype(auto) get(variant<Types...>&& value);
}
```

This prototype corresponds to the common header: `<asc/std/variant>`.

### Prototype 36

```cpp
namespace asc::std {
template<class T, class... Types>
constexpr decltype(auto) get(const variant<Types...>&& value);
}
```

This prototype corresponds to the common header: `<asc/std/variant>`.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T1` | The target element type for access by type; it must occur exactly once among the element types of the tuple. |
| `Args` | The list of element types of the tuple. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The tuple object to be accessed by type; returns an rvalue reference to the element of type T1 in it, which can be moved. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T1` | The target element type for access by type; it must occur exactly once among the element types of the tuple. |
| `Args` | The list of element types of the tuple. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The tuple object to be accessed by type; returns a reference to the element of type T1 in it. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T1` | The target element type for access by type; it must occur exactly once among the element types of the tuple. |
| `Args` | The list of element types of the tuple. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The read-only tuple object to be accessed by type; returns a const rvalue reference to the element of type T1 in it. |

### Parameters of Prototype 4

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T1` | The target element type for access by type; it must occur exactly once among the element types of the tuple. |
| `Args` | The list of element types of the tuple. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The read-only tuple object to be accessed by type; returns a const reference to the element of type T1 in it. |

### Parameters of Prototype 5

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T1` | The target member type for access by type; it must match the type of one member of the pair. |
| `T2` | The type of the other member of the pair. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The pair object to be accessed by type; returns an rvalue reference to the member of type T1 in it, which can be moved. |

### Parameters of Prototype 6

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T1` | The target member type for access by type; it must match the type of one member of the pair. |
| `T2` | The type of the other member of the pair. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The pair object to be accessed by type; returns an rvalue reference to the member of type T1 in it, which can be moved. |

### Parameters of Prototype 7

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T1` | The target member type for access by type; it must match the type of one member of the pair. |
| `T2` | The type of the other member of the pair. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The pair object to be accessed by type; returns a reference to the member of type T1 in it. |

### Parameters of Prototype 8

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T1` | The target member type for access by type; it must match the type of one member of the pair. |
| `T2` | The type of the other member of the pair. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The pair object to be accessed by type; returns a reference to the member of type T1 in it. |

### Parameters of Prototype 9

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T1` | The target member type for access by type; it must match the type of one member of the pair. |
| `T2` | The type of the other member of the pair. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The read-only pair object to be accessed by type; returns a const rvalue reference to the member of type T1 in it. |

### Parameters of Prototype 10

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T1` | The target member type for access by type; it must match the type of one member of the pair. |
| `T2` | The type of the other member of the pair. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The read-only pair object to be accessed by type; returns a const rvalue reference to the member of type T1 in it. |

### Parameters of Prototype 11

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T1` | The target member type for access by type; it must match the type of one member of the pair. |
| `T2` | The type of the other member of the pair. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The read-only pair object to be accessed by type; returns a const reference to the member of type T1 in it. |

### Parameters of Prototype 12

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T1` | The target member type for access by type; it must match the type of one member of the pair. |
| `T2` | The type of the other member of the pair. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The read-only pair object to be accessed by type; returns a const reference to the member of type T1 in it. |

### Parameters of Prototype 13

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | Member selector for complex, a compile-time constant; 0 selects the real part and 1 selects the imaginary part. |
| `T` | The scalar type of complex, i.e. the type of the real and imaginary parts. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The complex object whose real or imaginary part is to be accessed; Index 0 selects the real part and 1 selects the imaginary part, returning an rvalue reference. |

### Parameters of Prototype 14

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | Member selector for complex, a compile-time constant; 0 selects the real part and 1 selects the imaginary part. |
| `T` | The scalar type of complex, i.e. the type of the real and imaginary parts. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The complex object whose real or imaginary part is to be accessed; Index 0 selects the real part and 1 selects the imaginary part. |

### Parameters of Prototype 15

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | Member selector for complex, a compile-time constant; 0 selects the real part and 1 selects the imaginary part. |
| `T` | The scalar type of complex, i.e. the type of the real and imaginary parts. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The read-only complex object whose real or imaginary part is to be accessed; Index 0 selects the real part and 1 selects the imaginary part, returning a const rvalue reference. |

### Parameters of Prototype 16

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | Member selector for complex, a compile-time constant; 0 selects the real part and 1 selects the imaginary part. |
| `T` | The scalar type of complex, i.e. the type of the real and imaginary parts. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The read-only complex object whose real or imaginary part is to be accessed; Index 0 selects the real part and 1 selects the imaginary part. |

### Parameters of Prototype 17

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | The subscript of the target element, a compile-time constant; it must satisfy Index < sizeof...(T). |
| `T` | The list of element types of the tuple. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The read-only tuple object to be accessed by subscript; returns a const rvalue reference to the element at position Index. |

### Parameters of Prototype 18

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | The subscript of the target element, a compile-time constant; it must satisfy Index < sizeof...(T). |
| `T` | The list of element types of the tuple. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The read-only tuple object to be accessed by subscript; returns a const reference to the element at position Index. |

### Parameters of Prototype 19

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | The subscript of the target element, a compile-time constant; it must satisfy Index < sizeof...(T). |
| `T` | The list of element types of the tuple. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The tuple object to be accessed by subscript; returns an rvalue reference to the element at position Index, which can be moved. |

### Parameters of Prototype 20

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | The subscript of the target element, a compile-time constant; it must satisfy Index < sizeof...(T). |
| `T` | The list of element types of the tuple. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The tuple object to be accessed by subscript; returns a reference to the element at position Index. |

### Parameters of Prototype 21

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | The subscript of the target member, a compile-time constant; 0 selects first and 1 selects second. |
| `T1` | The type of the first member (first) of the pair. |
| `T2` | The type of the second member (second) of the pair. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The read-only pair object to be accessed by subscript; Index 0 selects first and 1 selects second, returning a const rvalue reference. |

### Parameters of Prototype 22

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | The subscript of the target member, a compile-time constant; 0 selects first and 1 selects second. |
| `T1` | The type of the first member (first) of the pair. |
| `T2` | The type of the second member (second) of the pair. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The read-only pair object to be accessed by subscript; Index 0 selects first and 1 selects second. |

### Parameters of Prototype 23

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | The subscript of the target member, a compile-time constant; 0 selects first and 1 selects second. |
| `T1` | The type of the first member (first) of the pair. |
| `T2` | The type of the second member (second) of the pair. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The pair object to be accessed by subscript; Index 0 selects first and 1 selects second, returning an rvalue reference. |

### Parameters of Prototype 24

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | The subscript of the target member, a compile-time constant; 0 selects first and 1 selects second. |
| `T1` | The type of the first member (first) of the pair. |
| `T2` | The type of the second member (second) of the pair. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The pair object to be accessed by subscript; Index 0 selects first and 1 selects second. |

### Parameters of Prototype 25

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | The subscript of the target element, a compile-time constant; it must satisfy Index < Size. |
| `T` | The element type of the array. |
| `Size` | The length of the array, a compile-time constant. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The array object to be accessed by subscript; returns an rvalue reference to the element at position Index, which can be moved. |

### Parameters of Prototype 26

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | The subscript of the target element, a compile-time constant; it must satisfy Index < Size. |
| `T` | The element type of the array. |
| `Size` | The length of the array, a compile-time constant. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The array object to be accessed by subscript; returns a reference to the element at position Index. |

### Parameters of Prototype 27

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | The subscript of the target element, a compile-time constant; it must satisfy Index < Size. |
| `T` | The element type of the array. |
| `Size` | The length of the array, a compile-time constant. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The read-only array object to be accessed by subscript; returns a const rvalue reference to the element at position Index. |

### Parameters of Prototype 28

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | The subscript of the target element, a compile-time constant; it must satisfy Index < Size. |
| `T` | The element type of the array. |
| `Size` | The length of the array, a compile-time constant. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The read-only array object to be accessed by subscript; returns a const reference to the element at position Index. |

### Parameters of Prototype 29

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | The compile-time index of the target alternative; it must be less than the number of types in Types. |
| `Types` | All alternative types of the variant, in declaration order. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The variant object, which must currently hold the selected alternative; the returned reference depends on the lifetime of its storage. |

### Parameters of Prototype 30

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | The compile-time index of the target alternative; it must be less than the number of types in Types. |
| `Types` | All alternative types of the variant, in declaration order. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The read-only variant object, which must currently hold the selected alternative; the returned reference depends on the lifetime of its storage. |

### Parameters of Prototype 31

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | The compile-time index of the target alternative; it must be less than the number of types in Types. |
| `Types` | All alternative types of the variant, in declaration order. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The variant object, which must currently hold the selected alternative; the returned reference depends on the lifetime of its storage. |

### Parameters of Prototype 32

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | The compile-time index of the target alternative; it must be less than the number of types in Types. |
| `Types` | All alternative types of the variant, in declaration order. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The read-only variant object, which must currently hold the selected alternative; the returned reference depends on the lifetime of its storage. |

### Parameters of Prototype 33

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The target alternative type; it must occur exactly once in Types. |
| `Types` | All alternative types of the variant, in declaration order. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The variant object, which must currently hold the selected alternative; the returned reference depends on the lifetime of its storage. |

### Parameters of Prototype 34

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The target alternative type; it must occur exactly once in Types. |
| `Types` | All alternative types of the variant, in declaration order. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The read-only variant object, which must currently hold the selected alternative; the returned reference depends on the lifetime of its storage. |

### Parameters of Prototype 35

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The target alternative type; it must occur exactly once in Types. |
| `Types` | All alternative types of the variant, in declaration order. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The variant object, which must currently hold the selected alternative; the returned reference depends on the lifetime of its storage. |

### Parameters of Prototype 36

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The target alternative type; it must occur exactly once in Types. |
| `Types` | All alternative types of the variant, in declaration order. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The read-only variant object, which must currently hold the selected alternative; the returned reference depends on the lifetime of its storage. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `T1 &&` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 2 | `T1 &` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 3 | `const T1 &&` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 4 | `const T1 &` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 5 | `T1 &&` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 6 | `T1 &&` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 7 | `T1 &` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 8 | `T1 &` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 9 | `const T1 &&` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 10 | `const T1 &&` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 11 | `const T1 &` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 12 | `const T1 &` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 13 | `T &&` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 14 | `T &` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 15 | `const T &&` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 16 | `const T &` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 17 | `const tuple_element_t<Index, tuple<T...>> &&` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 18 | `const tuple_element_t<Index, tuple<T...>> &` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 19 | `tuple_element_t<Index, tuple<T...>> &&` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 20 | `tuple_element_t<Index, tuple<T...>> &` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 21 | `const tuple_element_t<Index, pair<T1, T2>> &&` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 22 | `const tuple_element_t<Index, pair<T1, T2>> &` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 23 | `tuple_element_t<Index, pair<T1, T2>> &&` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 24 | `tuple_element_t<Index, pair<T1, T2>> &` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 25 | `T &&` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 26 | `T &` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 27 | `const T &&` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 28 | `const T &` | Returns a reference to the object; the referenced object must remain valid while the reference is in use. |
| Prototype 29 | `variant_alternative_t<Index, variant<Types...>>&` (deduced by decltype(auto)) | Returns the corresponding reference to the currently active alternative; when the active index does not match, a trap is triggered and bad_variant_access is not thrown. |
| Prototype 30 | `const variant_alternative_t<Index, variant<Types...>>&` (deduced by decltype(auto)) | Returns the corresponding reference to the currently active alternative; when the active index does not match, a trap is triggered and bad_variant_access is not thrown. |
| Prototype 31 | `variant_alternative_t<Index, variant<Types...>>&&` (deduced by decltype(auto)) | Returns the corresponding reference to the currently active alternative; when the active index does not match, a trap is triggered and bad_variant_access is not thrown. |
| Prototype 32 | `const variant_alternative_t<Index, variant<Types...>>&&` (deduced by decltype(auto)) | Returns the corresponding reference to the currently active alternative; when the active index does not match, a trap is triggered and bad_variant_access is not thrown. |
| Prototype 33 | `T&` (deduced by decltype(auto)) | Returns the corresponding reference to the currently active alternative; when the active index does not match, a trap is triggered and bad_variant_access is not thrown. |
| Prototype 34 | `const T&` (deduced by decltype(auto)) | Returns the corresponding reference to the currently active alternative; when the active index does not match, a trap is triggered and bad_variant_access is not thrown. |
| Prototype 35 | `T&&` (deduced by decltype(auto)) | Returns the corresponding reference to the currently active alternative; when the active index does not match, a trap is triggered and bad_variant_access is not thrown. |
| Prototype 36 | `const T&&` (deduced by decltype(auto)) | Returns the corresponding reference to the currently active alternative; when the active index does not match, a trap is triggered and bad_variant_access is not thrown. |

## Constraints

- When accessing by index, `Index` must be less than the number of elements of the corresponding object; an empty array and an empty tuple have no accessible elements. The valid indexes for pair and complex are 0 and 1.
- When accessing a tuple by type, the target type must occur at least once; the current implementation selects the first occurrence when duplicate types are present, which differs from the standard library rule requiring the type to be unique. When accessing a pair by type, the target type must occur exactly once, to avoid overload ambiguity.
- The returned reference preserves the const-qualification and value category of the corresponding prototype; when the element type is itself a reference, the final type also follows the reference collapsing rules.
- Returning an rvalue reference does not itself move the element; whether a move happens is decided by the caller's subsequent use of the returned reference.
- The returned reference does not extend the lifetime of the source object; it must be used while the source object is still valid, and a reference to an element of a local object must not be returned.
- The common headers annotated for each prototype must be included; the complex object itself is still subject to the current `complex<float>` support scope.
- Prototypes 1-28 are declared `noexcept`; the 8 variant overloads have no `noexcept` declaration. Element access performs no element construction, assignment, or comparison.

- Accessing a variant by index requires Index to be valid and the selected type to be non-void; accessing by type requires the target type to occur exactly once. The currently held index must match, otherwise the implementation directly traps; this differs from the standard library failure path that throws bad_variant_access. When a mismatch needs to be handled, holds_alternative or get_if can be used to check first.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/array>
#include <asc/std/variant>
#include <asc/std/type_traits>

bool example()
{
    asc::std::array<int, 2> values{{1, 2}};
    auto& first = asc::std::get<0>(values);
    static_assert(asc::std::is_same_v<decltype(first), int&>);
    first = 7;
    asc::std::variant<int, float> selected(3);
    if (!asc::std::holds_alternative<int>(selected)) return false;
    auto& active = asc::std::get<int>(selected);
    static_assert(asc::std::is_same_v<decltype(active), int&>);
    active = 9;
    return &first == &values[0] && values[0] == 7 && asc::std::get<0>(selected) == 9;
}
```

## Related APIs

- [API list for this header](asc_std_array.md)
