# `<asc/numeric_types>`: low-precision numeric formats

This header provides storage wrappers, encoded bit access, native-value bridges and explicit scalar conversions.
It supports C++17 and C++20. Host inclusion requires no CANN SDK. The wrappers are class types; standard integral,
floating_point and arithmetic traits remain false.

## Product Support

Host: no SDK. Device: BiSheng 15, dav-3510, strict floating configuration.

## Description

Storage, encoded bit access, native bridges and explicit conversions.

## Types and representation

| Type | Encoding | Size/alignment | Elements |
| --- | --- | --- | --- |
| `asc::float16` | binary16, sign/exponent/fraction 1/5/10, bias 15 | 2/2 | 1 |
| `asc::bfloat16` | BF16, 1/8/7, bias 127 | 2/2 | 1 |
| `asc::float8_e4m3fn` | E4M3FN, maximum finite 448, NaN, no Inf | 1/1 | 1 |
| `asc::float8_e5m2` | E5M2, maximum finite 57344, Inf/NaN | 1/1 | 1 |
| `asc::float8_e8m0` | Unsigned scale: codes 0..254 mean 2^(code-127); 255 is NaN | 1/1 | 1 |
| `asc::hifloat8` | Ascend HiFloat8, D selects exponent/fraction allocation | 1/1 | 1 |
| `asc::float4_e2m1x2` | Two E2M1 encodings; positive magnitudes 0, 0.5, 1, 1.5, 2, 3, 4, 6 | 1/1 | 2 |
| `asc::float4_e1m2x2` | Two E1M2 encodings; positive magnitudes 0, 0.25, 0.5, 0.75, 1, 1.25, 1.5, 1.75 | 1/1 | 2 |
| `asc::int4` | Four-bit two's complement [-8,7], upper nibble zero | 1/1 | 1 |
| `asc::int4x2` | Two four-bit two's-complement encodings | 1/1 | 2 |

The wrappers have standard layout and trivial default/copy/move construction, assignment and destruction.
Value initialization `T{}` produces zero bits, which mean 2^-127 for E8M0. An ordinary automatic `T x;` must be
written before reading. Copies preserve encoding. Numeric initialization uses numeric_convert explicitly.
Arithmetic and comparisons operate on values obtained by explicit conversion. Each int4 array element occupies
one byte; use int4x2 for compact storage.

SIMT uses ordinary pointers to read/write wrapper arrays. SIMD transfers the trivially-copyable GM/UB
representation into local scalar objects before bit access or conversion, using the compiler/SDK's
address-space-aware copy operations.

## Format registration and bit operations

All declarations below are in namespace asc. Fixed-width integer names refer to asc::std.

```cpp
enum class numeric_format {
    fp16 = 0, bf16 = 1, fp8_e4m3fn = 2, fp8_e5m2 = 3, fp8_e8m0 = 4,
    hif8 = 5, fp4_e2m1x2 = 6, fp4_e1m2x2 = 7, int4x2 = 8, int4 = 9
};
template<class T> struct numeric_format_traits;
template<class T>
constexpr typename numeric_format_traits<T>::storage_type to_bits(T value) noexcept;
template<class T>
constexpr T from_bits(typename numeric_format_traits<T>::storage_type bits) noexcept;
template<class Packed> constexpr Packed pack_elements(uint8_t low, uint8_t high) noexcept;
template<class Packed> constexpr uint8_t unpack_element(Packed value, unsigned index) noexcept;
```


numeric_format_traits accepts the ten unqualified value types. Its members are storage_type, format, bits,
storage_bits, lanes and has_native_type; native_type exists when a mapping is available. bits counts bits per
lane, storage_bits counts the complete encoding, and lanes counts elements. FP16/BF16 use uint16_t storage;
other wrappers use uint8_t. Metadata describes representation; conversion support has a separate query.

Bit operations preserve all valid encodings, including NaN sign and payload. int4 accepts only 0..15.
The FP4x2 types and int4x2 support packing: low/high each accept 0..15 and occupy the low/high nibble.
Indices 0/1 return zero-extended element encodings. Invalid encodings, nibble inputs or indices fail constant
evaluation and call asc::std::terminate at runtime. Check wider integers before converting them to parameter types.
Two-byte object storage follows the platform byte order; to_bits returns an integer encoding.

## Native-value interoperation

```cpp
template<class T> using native_numeric_t = typename numeric_format_traits<T>::native_type;
template<class T> native_numeric_t<T> to_native_numeric(T value) noexcept;
template<class T> T from_native_numeric(const native_numeric_t<T>& value) noexcept;
```


The initial Device adapter targets CANN 9.2.0-beta.2, BiSheng 15 and dav-3510.
FP16/BF16 map to half/bfloat16_t; FP8, HiFloat8 and FP4x2 map to the corresponding SDK builtins.
SIMD also provides int4x2_t. int4 has no mapping. Pure Host and other contexts report has_native_type=false,
provide no native_type, and reject bridge expressions by substitution. Bridges preserve encoded bits.
Trivially-copyable SDK int4x2_t uses bit copying; the qualified legacy class uses its public byte member. Pointer aliasing between wrappers and native
objects follows the caller's object-lifetime and address-space requirements.

## Explicit scalar conversions

```cpp
enum class rounding_mode { nearest_even = 0, toward_zero = 1, toward_positive = 2, toward_negative = 3 };
enum class saturation_mode { none = 0, finite = 1 };
template<class To, rounding_mode R = rounding_mode::nearest_even,
         saturation_mode S = saturation_mode::none, class From>
To numeric_convert(From value) noexcept;
template<class To, class From, rounding_mode R = rounding_mode::nearest_even,
         saturation_mode S = saturation_mode::none>
inline constexpr bool is_numeric_conversion_supported_v = /* configured support matrix */;
```


To/From are unqualified value types. The function and query share the same support predicate; false rejects the call.
The four floating types below are float16, bfloat16, float8_e4m3fn and float8_e5m2.

| Source | Destination | R | S |
| --- | --- | --- | --- |
| float | Four floating wrappers | All four | none/finite |
| Four floating wrappers | float | All four | none/finite |
| int32_t | int4 | All four, identical result | finite, clamp to [-8,7] |
| int4 | int32_t | All four, identical result | none/finite, sign extension |

Other combinations report false, including wrapper-to-wrapper, identity conversions, double, E8M0, HiFloat8,
packed formats and ordinary integer-to-integer conversions. Host floating conversion requires IEEE binary32 float.
The initial Device software path targets BiSheng 15/dav-3510 in SIMT and SIMD scalar contexts. Floating conversion
requires strict configuration; -ffast-math reports false. Unknown option values and other Device targets also report false.

Finite inputs round at the target precision with gradual underflow before range checking. nearest_even chooses the
even significand at a midpoint. With none, overflow produces signed Inf or maximum finite according to direction
for formats with Inf; E4M3FN produces canonical NaN. finite clamps overflow and source Inf to signed maximum finite.
none preserves source Inf in destinations with Inf; E4M3FN converts Inf to NaN. Signed zero is preserved, and underflow
produces subnormals or signed zero. Both saturation modes canonicalize NaNs, discarding sign/payload.
Canonical NaNs: FP16 0x7e00, BF16 0x7fc0, E4M3FN 0x7f, E5M2 0x7e, float 0x7fc00000.
Integer bit operations implement conversions independently of rounding, saturation and FTZ state. Floating exception
flags are unspecified.

## Constraints

Calls must satisfy the format, index, conversion and compilation conditions above.

## Example

```cpp
#include <asc/numeric_types>

int main()
{
    const auto stored = asc::numeric_convert<asc::float16>(1.5f);
    const float value = asc::numeric_convert<float>(stored);
    const auto packed = asc::pack_elements<asc::int4x2>(0x8, 0x7);
    const auto low = asc::from_bits<asc::int4>(asc::unpack_element(packed, 0));
    const auto signed_low = asc::numeric_convert<asc::std::int32_t>(low);
    return value == 1.5f && asc::to_bits(stored) == 0x3e00 && signed_low == -8 ? 0 : 1;
}
```


## Modules and delivery

The private storage definition is shared with type_traits. Generic classification belongs to type_traits;
ordinary checked integer conversions belong to numeric. CANN_ASC_STL_HAS_NUMERIC_TYPES is defined once in the
version product-information root and represents the complete minimum Issue #85 delivery and applicable acceptance.
Native acceleration, other chips and later format conversions have their own conditions. Consult the macro and PR
validation for the current delivery status.

Design: [Issue #85](https://gitcode.com/cann/asc-stl/issues/85).
Formats: [Ascend SIMD types](https://asc.gitcode.com/api/SIMD-API/basic_api/data_structures/builtin_data_types.html),
[OCP MX v1.0](https://www.opencompute.org/documents/ocp-microscaling-formats-mx-v1-0-spec-final-pdf).

## Related APIs

[type_traits](../../type_traits_and_utilities/asc_type_traits/asc_type_traits.md), [numeric](../asc_numeric/asc_numeric.md).
