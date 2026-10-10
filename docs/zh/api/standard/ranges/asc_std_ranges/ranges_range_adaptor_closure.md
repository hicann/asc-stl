# asc::std::ranges::range_adaptor_closure

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

`asc::std::ranges::range_adaptor_closure` 标记临时范围的不可借用结果或提供视图适配辅助能力。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 声明

```cpp
template<class T, enable_if_t<is_class_v<T>, int>, enable_if_t<same_as<T, remove_cv_t<T>>, int>> class asc::std::ranges::range_adaptor_closure
```

## 约束说明

- 七个列出名称
- 有限repeat、两路random-access+sized zip引用写回、单次range|closure
- Host、AI Core SIMD 编程 和 AI Core SIMT 编程

## 调用示例

以下片段用具体模板实参实例化类型；实际对象仍须满足本页构造与生命周期约束。

```cpp
#include <asc/std/ranges>

void use_type()
{
    using selected = asc::std::ranges::range_adaptor_closure<asc::std::ranges::single_view<int>>;
    (void)sizeof(selected);
}
```
