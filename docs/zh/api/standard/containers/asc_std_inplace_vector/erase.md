# asc::std::erase

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

头文件路径为：`<asc/std/inplace_vector>`。

`asc::std::erase`当前没有接受inplace_vector的自由函数重载。本页保留原入口用于兼容性说明；可用成员[`erase_if`](inplace_vector_erase_if.md)按条件移除元素。

## 函数原型

此自由函数重载未提供。替代接口为容器的成员erase_if，其原型及条件见[成员页面](inplace_vector_erase_if.md)。

## 参数说明

本页不声明自由函数参数。示例在现有容器上调用成员erase_if。

## 返回值说明

本页不声明自由函数返回值；替代成员erase_if返回移除的元素数量。

## 约束说明

- 替代的成员`erase_if`从C++17起提供；Host和Device使用均须满足该成员的非抛出操作条件。

- 使用所链接成员的谓词、元素操作及生命周期条件；不调用不存在的自由函数。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/inplace_vector>

bool example()
{
    asc::std::inplace_vector<int, 4> values;
    if (!values.try_push_back(2) || !values.try_push_back(3)) return false;
    const auto removed = values.erase_if([](int value) { return value == 2; });
    return removed == 1 && values.size() == 1 && values[0] == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_inplace_vector.md)
