# CANN_ASC_STL

## 产品支持情况

C++17 为最低要求，同时支持 C++20；Host、SIMD、SIMT 可独立包含，宏值与芯片无关。

## 功能说明

`<asc/version>`：公历发行日期，十进制格式为 `YYYYMMDD`。本发行包固定为 `20261023`，可直接比较先后。

## 声明

```cpp
#define CANN_ASC_STL 20261023
```

## 约束说明

宏值由发布流程固定，使用有效公历日期，四位年份范围为 1000–9999；调用方编译日期及编译模式不改变该值。同日快照通过发行提交区分。

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
- [维护规则及交付记录](../../../../guide/product_version.md)
