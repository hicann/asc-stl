# asc::std::decay::type

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

头文件路径为：`<asc/std/type_traits>`。

`asc::std::decay::type`提供该类型特征、映射或适配器计算出的成员类型。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

`asc::std::decay<T>::type`先移去T的引用：数组转成指向元素的指针，函数转成函数指针，其余类型移去顶层cv限定。

```cpp
using ArrayResult = asc::std::decay<int[3]>::type;  // int*
using ValueResult = asc::std::decay<const int&>::type; // int
```

## 约束说明

- 提供特征类以及标准的 _t、_v辅助形式。

## 调用示例

以下Host示例使用独立的预期类型或值检查接口结果。

```cpp
#include <asc/std/type_traits>

using result_type = typename asc::std::decay<const int&>::type;
static_assert(asc::std::is_same_v<result_type, int>);
static_assert(asc::std::is_same_v<asc::std::decay_t<int[3]>, int*>);
```

## 关联API

- [本头文件的接口列表](asc_std_type_traits.md)
