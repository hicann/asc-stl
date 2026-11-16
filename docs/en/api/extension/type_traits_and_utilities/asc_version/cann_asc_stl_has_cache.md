# CANN_ASC_STL_HAS_CACHE

## 产品支持情况

Requires C++17 and also supports C++20. The header is independently includable in Host, SIMD and SIMT compilation. Macro values are independent of the chip.

## 功能说明

`<asc/version>`：Reports delivery of the baseline cache-control API described in [Issue #99](https://gitcode.com/cann/asc-stl/issues/99). The current value is `0`.

## 声明

```cpp
#define CANN_ASC_STL_HAS_CACHE 0
```

## 约束说明

The macro is always defined as `0` or `1`. A value of `1` requires the complete baseline API and its applicable acceptance; otherwise it is `0`. Test its value with `#if`. Consult the module for operation-specific chip, type, address-space and execution-mode requirements.

## 调用示例

```cpp
#include <asc/version>

#if CANN_ASC_STL_HAS_CACHE
constexpr bool use_extension = true;
#else
constexpr bool use_extension = false;
#endif
static_assert(use_extension == (CANN_ASC_STL_HAS_CACHE == 1));
```

## 关联API

- [<asc/version>](asc_version.md)
- [Maintenance and delivery records](../../../../guide/product_version.md)
