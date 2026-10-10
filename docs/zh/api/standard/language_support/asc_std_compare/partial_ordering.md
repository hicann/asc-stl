# asc::std::partial_ordering

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

头文件路径为：`<asc/std/compare>`。

`asc::std::partial_ordering` 表示可包含无序状态的部分排序结果。

标准语义参考：[cppreference `compare`](https://en.cppreference.com/w/cpp/header/compare)。

## 声明

```cpp
class asc::std::partial_ordering
```

## 约束说明

- 支持 ASC 比较类别常量、与零比较以及标准类别转换

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/compare>

void use_type(const asc::std::partial_ordering& value)
{
    (void)value;
}
```
