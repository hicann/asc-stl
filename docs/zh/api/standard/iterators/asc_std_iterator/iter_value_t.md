# asc::std::iter_value_t

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

头文件路径为：`<asc/std/iterator>`。

`asc::std::iter_value_t` 按名称所指的范围或迭代器属性计算结果类型。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 声明

```cpp
template<class Index> using asc::std::iter_value_t = typename Selecttraits<remove_cvref_t<Index>, indirectly_readable_traits<remove_cvref_t<Index>>>::value_type
```

## 约束说明

- 提供 C++20 公开迭代器概念和特征接口

## 调用示例

以下 Host 片段用具体迭代器或容器类型实例化本页接口。

```cpp
#include <asc/std/iterator>

#include <asc/std/type_traits>

void example()
{
    using selected = asc::std::iter_value_t<int*>;
    static_assert(asc::std::is_same_v<selected, selected>);
}
```
