# asc::std::complex::complex

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

Header: `<asc/std/complex>`.

`asc::std::complex::complex` initializes a `complex` object with the constructor forms listed on this page.

Standard semantics reference: [cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex).

## Function Prototype

Member of: [`asc::std::complex<T>`](complex.md). Currently `T` supports only `float`. The following are the constructor declarations directly usable for this type.

### Default and Scalar Construction

```cpp
constexpr complex(const T& real = T(), const T& imag = T()) noexcept;
```

### Copy Construction

```cpp
constexpr complex(const complex& other) noexcept = default;
```

### Move Construction

```cpp
constexpr complex(complex&& other) noexcept = default;
```

### Host System Complex Conversion

```cpp
template<class U>
complex(const ::std::complex<U>& other) noexcept;
```

The last form can be called on the Host only and converts the two components of the system complex number to `float` respectively. The conversion template between ASC complex numbers does not relax the restrictions on the target and source ASC types; `asc::std::complex<double>` cannot be instantiated, so this page does not list it as an available input.

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Component type of the owning ASC complex number; currently must be `float`. |
| `U` | Component type of the Host system complex number input; must be convertible via `static_cast<float>`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `real` | Input | Initial real part; 0 when omitted. |
| `imag` | Input | Initial imaginary part; 0 when omitted. |
| `other` | Input | Source complex number providing the real part and the imaginary part; system complex conversion may lose precision. |

## Return Value

No return value.

## Constraints

- `asc::std::complex` currently supports only the `float` component type; when the source is a system `::std::complex<U>`, the ASC source type restriction does not apply, but the conversion can be performed on the Host only.
- Copy and move construction copy the two floating-point components and do not borrow the source object's storage.
- The default and ASC same-type constructors can be used in the corresponding Host/device programming modes; system complex conversion requires the Host standard library.
- For `volatile`-qualified component access and setter members, see the individual member pages; they do not change the constructor overload set here.

## Example

The following Host example provides concrete inputs and checks the results.

```cpp
#include <complex>
#include <asc/std/complex>
#include <asc/std/utility>

bool example()
{
    asc::std::complex<float> zero;
    asc::std::complex<float> scalar(2.0F);
    asc::std::complex<float> value(2.0F, 3.0F);
    const auto copy = value;
    const auto moved = asc::std::move(value);
    const asc::std::complex<float> converted(::std::complex<double>(4.0, 5.0));
    return zero.real() == 0.0F && scalar.imag() == 0.0F && copy.imag() == 3.0F &&
        moved.real() == 2.0F && converted.real() == 4.0F && converted.imag() == 5.0F;
}
```

## Related APIs

- [API list for this header](asc_std_complex.md)
