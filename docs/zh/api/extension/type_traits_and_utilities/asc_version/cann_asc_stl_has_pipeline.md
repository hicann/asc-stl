# CANN_ASC_STL_HAS_PIPELINE

## 产品支持情况

C++17 为最低要求，同时支持 C++20；Host、SIMD、SIMT 可独立包含，宏值与芯片无关。

## 功能说明

`<asc/version>`：标识是否交付 [Issue #105](https://gitcode.com/cann/asc-stl/issues/105) 约定的 SIMT 线程组流水线基础接口。当前为 `0`。

## 声明

```cpp
#define CANN_ASC_STL_HAS_PIPELINE 0
```

## 约束说明

宏始终定义为 `0` 或 `1`。`0` 表示基础接口尚未全部交付并通过适用验收，`1` 表示已全部交付并通过适用验收。用 `#if` 判断值。具体操作的芯片、类型、地址空间及执行模式要求见对应模块。

## 调用示例

```cpp
#include <asc/version>

#if CANN_ASC_STL_HAS_PIPELINE
constexpr bool use_extension = true;
#else
constexpr bool use_extension = false;
#endif
static_assert(use_extension == (CANN_ASC_STL_HAS_PIPELINE == 1));
```

## 关联API

- [<asc/version>](asc_version.md)
- [维护规则及交付记录](../../../../guide/product_version.md)
