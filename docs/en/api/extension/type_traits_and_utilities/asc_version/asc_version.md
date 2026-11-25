# Header asc/version

Provides the ASC-STL release date and three extension API delivery flags, and includes the standard-layer `CANN_ASC_STL_LIB_*` feature macros. The four product macros have identical values across Host, SIMD, SIMT and C++17/C++20 compilation for a given package.

```cpp
#include <asc/version>
```

| API | Kind | C++ modes | Availability | Chip dependence |
| --- | --- | --- | --- | --- |
| [CANN_ASC_STL](cann_asc_stl.md) | Macro | C++17/C++20 | Host, SIMD, SIMT | None |
| [CANN_ASC_STL_HAS_PIPELINE](cann_asc_stl_has_pipeline.md) | Macro | C++17/C++20 | Host, SIMD, SIMT | None |
| [CANN_ASC_STL_HAS_NUMERIC_TYPES](cann_asc_stl_has_numeric_types.md) | Macro | C++17/C++20 | Host, SIMD, SIMT | None |
| [CANN_ASC_STL_HAS_CACHE](cann_asc_stl_has_cache.md) | Macro | C++17/C++20 | Host, SIMD, SIMT | None |

[Product version guide](../../../../guide/product_version.md)
