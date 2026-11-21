# asc::std::variant::`operator=`

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

`asc::std::variant::operator=` updates the object with the selected assignment overload and returns the specified result.

Standard semantics reference: [cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant).

## Function Prototype

Member of: [`asc::std::variant<Types...>`](variant.md). The following are declarations inside the class; unnamed constraint parameters and the default index are used to select overloads, and the caller does not need to specify them.

### Copy assignment

```cpp
constexpr variant& operator=(const variant& other);
```

### Move assignment

```cpp
constexpr variant& operator=(variant&& other);
```

### Converting value assignment

```cpp
template <class T, size_t Index = __variant_best_match<remove_cvref_t<T>, void, Types...>::value,
    enable_if_t<Index != variant_npos &&
            (is_assignable_v<variant_alternative_t<Index, variant>&, T> ||
                is_constructible_v<variant_alternative_t<Index, variant>, T>),
        int> = 0>
constexpr variant& operator=(T&& value);
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Types` | The list of alternative types of the owning `variant`; it must not contain arrays, references, or `void`. |
| `T` | The input type of converting value assignment; deduced from the argument and used to select the alternative type that can receive the value. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input; Input/Output when swapping | A same-type source object; the rvalue form may move its active alternative value, and a swap changes both objects. |
| `value` | Input (may be moved) | The value used to select and construct or assign the active alternative. |

## Return Value

Returns a reference to the current `variant` object, i.e. `*this`.

## Constraints

- On Host, copy assignment to a different alternative preserves the old value if copying the new alternative throws and moving it is nonthrowing. In other cases that construct the new alternative in place, a construction failure leaves the object valueless.
- A failed construction while switching alternatives does not preserve the old value; this implementation does not promise to preserve the old alternative through an extra temporary copy.
- A failed assignment to the same active alternative does not end the object's lifetime; the index stays unchanged and the state of the value is determined by that alternative type's assignment operation.
- After copy or move assignment from a source with no active alternative, the target likewise has no active alternative.

- The object holds one active alternative value at a time; the selected alternative must be confirmed through `index()` before reading.
- Alternative types used on the device and their construction, assignment, destruction, and swap operations must be available in the corresponding programming mode and must not throw.
- Assignment to the same active type requires the corresponding assignment expression to be available; switching the active type requires the target type to be constructible from the source value.

## Example

The following Host example uses a concrete object and checks the result of the call.

```cpp
#include <asc/std/variant>

bool example()
{
    asc::std::variant<int, float> value(7);
    value = 2.5F;
    return value.index() == 1 && asc::std::get<1>(value) == 2.5F;
}
```

## Related APIs

- [`asc::std::variant`](variant.md)
- [API list for this header](asc_std_variant.md)
