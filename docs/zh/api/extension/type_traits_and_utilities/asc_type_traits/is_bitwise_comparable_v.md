# asc::is_bitwise_comparable_v

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

头文件路径为：`<asc/type_traits>`。

`asc::is_bitwise_comparable_v<T>` 是 `is_bitwise_comparable<T>::value` 的 bool 变量模板简写。

## 声明

```cpp
template<class T> inline constexpr bool asc::is_bitwise_comparable_v = asc::is_bitwise_comparable<T>::value
```

## 约束说明

- 结果是对应定制点返回值的精确 bool 投影

## 调用示例

以下片段用具体模板实参读取接口值。

```cpp
#include <asc/type_traits>

inline constexpr auto example = asc::is_bitwise_comparable_v<int>;
```
