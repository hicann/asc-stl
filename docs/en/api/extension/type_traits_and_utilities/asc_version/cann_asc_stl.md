# CANN_ASC_STL

## 产品支持情况

Requires C++17 and also supports C++20. The header is independently includable in Host, SIMD and SIMT compilation. Macro values are independent of the chip.

## 功能说明

`<asc/version>`：Gregorian release date encoded as a decimal `YYYYMMDD` integer. This package fixes it at `20261023`; ordinary integer comparisons order release dates.

## 声明

```cpp
#define CANN_ASC_STL 20261023
```

## 约束说明

The release process fixes a valid Gregorian date with a four-digit year from 1000 to 9999. Compilation date and mode leave it unchanged. Release commits distinguish snapshots from the same day.

## 调用示例

```cpp
#include <asc/version>

// 20260101 is an illustrative minimum release date.
#if CANN_ASC_STL < 20260101
#error "ASC-STL release 20260101 or newer is required"
#endif
static_assert(CANN_ASC_STL >= 20260101);
```

## 关联API

- [<asc/version>](asc_version.md)
- [Maintenance and delivery records](../../../../guide/product_version.md)
