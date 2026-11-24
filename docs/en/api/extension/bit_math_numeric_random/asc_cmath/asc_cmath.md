# Header asc/cmath

## Usage

```cpp
#include <asc/cmath>
```

## Description

Exact scalar integer mathematics and paired sine/cosine in radians. Requires C++17 and supports C++20.

| API | Purpose |
| --- | --- |
| [asc::ceil_div](ceil_div.md) | Returns the exact integer quotient rounded toward positive infinity, for all signed operand combinations. |
| [asc::floor_div](floor_div.md) | Returns the exact integer quotient rounded toward negative infinity, rather than C++ truncation toward zero. |
| [asc::round_up](round_up.md) | Returns the smallest multiple of a positive integer b that is not less than nonnegative a. |
| [asc::integer_pow](integer_pow.md) | Computes an exact nonnegative integer power, returning the base type T. |
| [asc::integer_sqrt](integer_sqrt.md) | Returns the exact floor square root r in T, satisfying the unbounded mathematical relation r² <= value < (r+1)². |
| [asc::mul_hi](mul_hi.md) | For W unsigned value bits of T, returns floor(left*right/2^W), the high W bits of the full mathematical product. |
| [asc::sincos](sincos.md) | Takes an angle in radians, writes its sine to sin_out and cosine to cos_out, and returns void. |

Integer templates preserve T; sincos is selected by type and execution space. Each API page specifies its preconditions, special values, accuracy and output-object requirements.
