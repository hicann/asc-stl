# asc::sincos

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

Header: `<asc/cmath>`.

`asc::sincos` computes the sine and cosine of the input value in a single call and writes them to two output pointers respectively.

## Function Prototype

### Prototype 1

```cpp
namespace asc {
void sincos(float value, float* sin_out, float* cos_out) noexcept;
} // namespace asc
```

### Prototype 2

```cpp
namespace asc {
void sincos(double value, double* sin_out, double* cos_out) noexcept;
} // namespace asc
```

### Prototype 3

```cpp
namespace asc {
void sincos(long double value, long double* sin_out, long double* cos_out) noexcept;
} // namespace asc
```

### Prototype 4

```cpp
namespace asc {
template<class T> void sincos(T value, double* sin_out, double* cos_out) noexcept;
} // namespace asc
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Angle expressed in radians, of type `float`; the sine and cosine of this angle are computed respectively. |
| `sin_out` | Output | Output parameter that receives the sine of the input value; the pointer must be valid (pointing to a writable `float`). |
| `cos_out` | Output | Output parameter that receives the cosine of the input value; the pointer must be valid (pointing to a writable `float`). |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Angle expressed in radians, of type `double`; the sine and cosine of this angle are computed respectively. |
| `sin_out` | Output | Output parameter that receives the sine of the input value; the pointer must be valid (pointing to a writable `double`). |
| `cos_out` | Output | Output parameter that receives the cosine of the input value; the pointer must be valid (pointing to a writable `double`). |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Angle expressed in radians, of type `long double`; the sine and cosine of this angle are computed respectively. |
| `sin_out` | Output | Output parameter that receives the sine of the input value; the pointer must be valid (pointing to a writable `long double`). |
| `cos_out` | Output | Output parameter that receives the cosine of the input value; the pointer must be valid (pointing to a writable `long double`). |

### Parameters of Prototype 4

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Type of the integer input value; must be an integer or enumeration type. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Integer value whose sine and cosine are to be computed; converted to double internally before computation. |
| `sin_out` | Output | Output parameter that receives the sine of the input value; the pointer must be valid (pointing to a writable `double`). |
| `cos_out` | Output | Output parameter that receives the cosine of the input value; the pointer must be valid (pointing to a writable `double`). |

## Return Value

No return value.

## Constraints

- sin_out and cos_out must not be null.
- The float overload can be called in Host and AI Core SIMT programming; the other overloads can only be called on the Host.
- The template overload requires T to be an integer or enumeration type.

## Example

The following Host example uses a concrete object and checks the result of the call.

```cpp
#include <asc/cmath>

bool example()
{
    float sf = 1.0F, cf = 0.0F;
    double sd = 1.0, cd = 0.0;
    long double sl = 1.0L, cl = 0.0L;
    asc::sincos(0.0F, &sf, &cf);
    asc::sincos(0.0, &sd, &cd);
    asc::sincos(0.0L, &sl, &cl);
    return sf == 0.0F && cf == 1.0F && sd == 0.0 && cd == 1.0 && sl == 0.0L && cl == 1.0L;
}
```

## Related APIs

- [API list for this header](asc_cmath.md)
