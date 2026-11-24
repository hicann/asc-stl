# Header asc/numeric

Provides checked scalar integer arithmetic and conversions with numeric results and failure flags.

| API | Kind | Language | Context |
| --- | --- | --- | --- |
| [asc::add_overflow](add_overflow.md) | Function template | C++17 / C++20 | Host / SIMD / SIMT |
| [asc::sub_overflow](sub_overflow.md) | Function template | C++17 / C++20 | Host / SIMD / SIMT |
| [asc::mul_overflow](mul_overflow.md) | Function template | C++17 / C++20 | Host / SIMD / SIMT |
| [asc::div_overflow](div_overflow.md) | Function template | C++17 / C++20 | Host / SIMD / SIMT |
| [asc::overflow_cast](overflow_cast.md) | Function template | C++17 / C++20 | Host / SIMD / SIMT |
| [asc::checked_result](checked_result.md) | Class template | C++17 / C++20 | Host / SIMD / SIMT |
| [asc::checked_result::value](checked_result_value.md) | Public member | C++17 / C++20 | Host / SIMD / SIMT |
| [asc::checked_result::failed](checked_result_failed.md) | Public member | C++17 / C++20 | Host / SIMD / SIMT |

The four arithmetic operations each have object and output-reference forms, for nine function-template overloads in total.

**Compatibility**

The old overflow_result/overflow names are replaced by checked_result/failed, and every failed value is zero. The five ordinary saturation extensions, narrow and narrow_cast are removed. Use overflow_cast for checked conversions and static_cast for unchecked conversions. Ordinary saturation remains subject to standard-layer version planning; this change does not add or claim standard saturation conformance.
