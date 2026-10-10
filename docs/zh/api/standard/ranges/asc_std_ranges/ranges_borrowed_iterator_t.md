# asc::std::ranges::borrowed_iterator_t

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

头文件路径为：`<asc/std/ranges>`。

`asc::std::ranges::borrowed_iterator_t` 按名称所指的范围或迭代器属性计算结果类型。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 声明

```cpp
template<class Rp> using asc::std::ranges::borrowed_iterator_t = If<borrowed_range<Rp>, iterator_t<Rp>, dangling>
```

## 约束说明

- 支持数组和用户范围，不支持仅由花括号构成的 initializer_list 表达式

## 调用示例

以下片段选用具体模板实参展示别名类型。

```cpp
#include <asc/std/ranges>

void use_type()
{
    using selected = asc::std::ranges::borrowed_iterator_t<int (&)[4]>;
}
```
