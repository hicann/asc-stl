# asc::std::aligned_accessor::aligned_accessor

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

Header: `<asc/std/mdspan>`.

`asc::std::aligned_accessor::aligned_accessor` initializes an `aligned_accessor` object with the construction forms listed on this page.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Function Prototype

Member of: [`aligned_accessor<Element, ByteAlignment>`](aligned_accessor.md). Expresses the same array pointer convertibility condition with public type traits.

### Prototype 1

```cpp
constexpr aligned_accessor() noexcept = default;
```

### Prototype 2

```cpp
template<class OtherElement, size_t OtherByteAlignment,
    enable_if_t<is_convertible_v<OtherElement (*)[], Element (*)[]>
        && (OtherByteAlignment >= ByteAlignment), int> = 0>
constexpr aligned_accessor(aligned_accessor<OtherElement, OtherByteAlignment> other) noexcept;
```

### Prototype 3

```cpp
template<class OtherElement,
    enable_if_t<is_convertible_v<OtherElement (*)[], Element (*)[]>, int> = 0>
constexpr explicit aligned_accessor(default_accessor<OtherElement> accessor) noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `OtherElement` | The element type of the source aligned accessor; it must be compatible with the element type of this accessor. |
| `OtherByteAlignment` | The byte alignment value of the source aligned accessor, a compile-time constant; it must not be smaller than this accessor's `ByteAlignment`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The other aligned accessor to be converted; its byte alignment is not lower than this accessor's `byte_alignment`, and this object obtains an access policy equivalent to it. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `OtherElement` | The element type of the source `default_accessor`; it must be compatible with the element type of this accessor. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `accessor` | Input | The `default_accessor` object being converted; it explicitly adds the `ByteAlignment` alignment assumption; the caller must ensure that base addresses subsequently handed to this accessor satisfy that alignment. |

## Return Value

No return value.

## Constraints

- `ByteAlignment` must be a non-negative integer power of two and not smaller than `alignof(Element)`.
- When converting from `aligned_accessor`, the element array pointers must be convertible and the source alignment must not be smaller than the target `ByteAlignment`.
- Converting from `default_accessor` does not check or fix addresses; base addresses input to subsequent access/offset must satisfy `ByteAlignment`.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/mdspan>

bool example()
{
    alignas(16) int values[4] = {1, 2, 3, 4};
    const asc::std::default_accessor<int> original;
    const asc::std::aligned_accessor<int, 16> accessor(original);
    int& result = accessor.access(values, 1);
    return &result == values + 1 && result == 2;
}
```

## Related APIs

- [API list for this header](asc_std_mdspan.md)
