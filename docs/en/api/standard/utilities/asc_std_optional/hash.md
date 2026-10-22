# asc::std::hash

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

Header: `<asc/std/optional>`.

`asc::std::hash<asc::std::optional<T>>` is provided by `<asc/std/optional>`, a hash specialization for optional: an empty value hashes to 0, and an engaged value hashes to hash<remove_const_t<T>>{}(*value); it can serve as the hasher selected by unordered containers, provided the hash and the equality relation of the contained value are consistent.

Standard semantics reference: [cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional).

## Function Prototype

```cpp
template <class T> struct hash<optional<T>> { size_t operator()(const optional<T>& value) const; };
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The type of the value contained in the optional; its hash<remove_const_t<T>> must be callable and consistent with the equality relation. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The optional object whose hash is computed; the hash value is 0 when it contains no value, and hash<remove_const_t<T>>{}(*value) when it does. |

## Return Value

| Return type | Description |
| --- | --- |
| `size_t` | Returns 0 for an empty optional; returns the hash result of the stored value when engaged. |

## Constraints

- The inner `hash<remove_const_t<T>>` must be callable and return the same result for equal T values; callability is only a necessary condition.
- The hash value of an empty optional is 0; an engaged value returns hash<remove_const_t<T>>{}(*value).
- `operator()` accepts const optional<T>& and returns size_t, and can be used by unordered containers that select this hasher and adopt a compatible key equality relation.
- If the element type falls into the [object byte fallback](../asc_std_bitset/hash.md), deterministic bytes and consistent representation for equivalent objects are likewise required; user types with padding, fields ignored by equality comparison, or non-trivial state must provide a suitable custom hash. Wrapping in optional does not fix a mismatch between the inner hash and the equality relation.

## Example

The following Host example checks the hash rules for the empty and engaged states.

```cpp
#include <asc/std/optional>
#include <asc/std/functional>

bool example()
{
    asc::std::optional<int> empty;
    asc::std::optional<int> value(7);
    asc::std::hash<asc::std::optional<int>> hasher;
    return hasher(empty) == 0 && hasher(value) == asc::std::hash<int>{}(7);
}
```

## Related APIs

- [API list for this header](asc_std_optional.md)
