# asc::std::ratio_multiply

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

头文件路径为：`<asc/std/ratio>`。

`asc::std::ratio_multiply` 按名称所指的算术或比较关系组合两个编译期有理数。

标准语义参考：[cppreference `ratio`](https://en.cppreference.com/w/cpp/header/ratio)。

## 声明

```cpp
template<class R1, class R2> using asc::std::ratio_multiply = typename __ratio_multiply<R1, R2>::type
```

## 约束说明

- 提供完整的 C++20 ratio 接口

## 调用示例

以下片段选用具体模板实参展示别名类型。

```cpp
#include <asc/std/ratio>

void use_type()
{
    using selected = asc::std::ratio_multiply<asc::std::ratio<1, 2>, asc::std::ratio<1, 3>>;
}
```
