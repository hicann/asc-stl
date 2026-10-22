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

Header: `<asc/std/bitset>`, `<asc/std/functional>`, `<asc/std/variant>`.

`asc::std::hash<T>` provides a hash function object returning `size_t`. Existing arithmetic, pointer, enum, and other value-type specializations are handled by their own dedicated rules; the primary template also retains the object-byte fallback for non-enum types. When using the fallback to compute hashes for container keys, the object representation and equality relation conditions below must be satisfied; being "callable" by itself does not guarantee that the hash requirements for keys are satisfied.

Standard semantics reference: [cppreference `hash`](https://en.cppreference.com/w/cpp/utility/hash).

## Declaration

### Prototype 1

```cpp
namespace asc::std {
template<class T> struct hash;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/functional>`.

### Prototype 2

```cpp
namespace asc::std {
template<class... Types> struct hash<asc::std::variant<Types...>>;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/variant>`.

### Prototype 3

```cpp
namespace asc::std {
template<size_t Size> struct hash<asc::std::bitset<Size>>;
} // namespace asc::std
```

This prototype corresponds to the header: `<asc/std/bitset>`.

## Constraints

- For the key equality relation used by a container, if `Equal(a, b)` is `true`, `Hash(a) == Hash(b)` must hold; hash collisions are allowed for unequal keys. When a custom equality relation is selected, the hash must also be consistent with it.
- The non-enum primary template without a corresponding specialization hashes all object bytes. This is a retained product extension and does not mean that any user type automatically satisfies the standard Hash requirements. Only domains where all read bytes are deterministic and every pair of equivalent keys has the same object representation may use this fallback as the key hash; being trivially copyable alone is not sufficient.
- When a key contains padding bytes that may vary, fields ignored by the equality test, or non-trivial object state, a custom hash computed by value semantics must be provided. You may explicitly specify `Hash` for an unordered container, or provide a hash specialization for the user type consistent with its equality relation; the caller must not expect the fallback to automatically recognize these fields.
- The enum primary template hashes by the underlying integer type; the provided arithmetic, pointer, and `nullptr_t` specializations are invoked according to their declarations, and the fallback rules above must not be applied to the processing paths of existing specializations.
- The `variant<Types...>` specialization combines the hash of the active alternative value and the index; in the `valueless_by_exception` state, a fixed empty-alternative sentinel value participates in the combination. The hash of each alternative value must also be consistent with its equality test. A callable hash for an alternative type does not mean this semantic requirement is already satisfied.
- The `bitset<Size>` specialization hashes by the bit sequence; the call is `constexpr` and does not throw.

## Example

The following Host example uses two equal keys with the same `id` and different `cache`; the custom hash only processes the `id` that participates in the equality test.

```cpp
#include <asc/std/bitset>
#include <asc/std/functional>
#include <asc/std/type_traits>

struct example_key {
    int id;
    int cache;
    friend bool operator==(const example_key& left, const example_key& right) noexcept
    {
        return left.id == right.id;
    }
};

struct example_hash {
    asc::std::size_t operator()(const example_key& value) const noexcept
    {
        return asc::std::hash<int>{}(value.id);
    }
};

struct example_equal {
    bool operator()(const example_key& left, const example_key& right) const noexcept
    {
        return left == right;
    }
};

static_assert(asc::std::is_trivially_copyable_v<example_key>);

bool example_key_hash()
{
    const example_key first{7, 1};
    const example_key second{7, 99};
    const example_hash key_hash;
    return first == second && first.cache != second.cache
        && key_hash(first) == key_hash(second);
}

bool example()
{
    const asc::std::bitset<8> first_bits(5), second_bits(5);
    const asc::std::hash<asc::std::bitset<8>> bits_hash;
    return first_bits == second_bits && bits_hash(first_bits) == bits_hash(second_bits)
        && example_key_hash();
}
```

## Related APIs

- [Hash and equality constraints of unordered_map](../../containers/asc_std_unordered_map/unordered_map.md)
- [Hash and equality constraints of unordered_set](../../containers/asc_std_unordered_set/unordered_set.md)
- [API list for this header](asc_std_bitset.md)
