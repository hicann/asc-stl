# asc::proclaims_copyable_arguments_v

## 产品支持情况

<!-- npu="950" id1 -->
- Ascend 950PR&950DT系列产品：支持
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3系列产品：不支持
<!-- end id2 -->
<!-- npu="910b" id3 -->
- Atlas A2系列产品：不支持
<!-- end id3 -->
<!-- npu="310b" id4 -->
- Atlas 200I/500 A2推理产品：不支持
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas推理系列产品AI Core：不支持
<!-- end id5 -->
<!-- npu="310p" id6 -->
- Atlas推理系列产品Vector Core：不支持
<!-- end id6 -->
<!-- npu="910" id7 -->
- Atlas训练系列产品：不支持
<!-- end id7 -->

## 功能说明

头文件路径为：`<asc/functional>`。

`asc::proclaims_copyable_arguments_v` 表示函数对象是否声明给定参数可安全按值复制。

## 声明

```cpp
template<class Function, class... Args> inline constexpr bool asc::proclaims_copyable_arguments_v = asc::proclaims_copyable_arguments<Function, Args...>::value
```

## 约束说明

- 整数或逻辑运算仅在数学性质成立时报告对应特性
- 浮点加法不满足结合律

## 调用示例

以下片段用具体模板实参读取接口值。

```cpp
#include <asc/functional>

inline constexpr auto example = asc::proclaims_copyable_arguments_v<asc::always_true, int>;
```
