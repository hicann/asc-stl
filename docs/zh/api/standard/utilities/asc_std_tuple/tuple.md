# asc::std::tuple

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

头文件路径为：`<asc/std/tuple>`。

`asc::std::tuple`按位置保存多个不同类型的元素。

标准语义参考：[cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple)。

## 声明

```cpp
namespace asc::std {
template<class... Types> class tuple;
}
```

## 约束说明

- 工具本身不额外分配容器存储；元素构造、赋值、交换或传入可调用体仍可按其自身语义分配或抛出，不能据此保证整个调用不分配。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/tuple>

bool example()
{
    asc::std::tuple<int, float> values(7, 2.0F);
    return asc::std::get<0>(values) == 7 && asc::std::get<1>(values) == 2.0F;
}
```

## 关联API

- [本头文件的接口列表](asc_std_tuple.md)
