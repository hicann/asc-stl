# asc::std::add_volatile::type

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

`asc::std::add_volatile::type`提供该类型特征、映射或适配器计算出的成员类型。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

所属类型：[`asc::std::add_volatile`](add_volatile.md)。

```cpp
// asc::std::add_volatile 类内的声明节选；模板形参和其他成员由所属类提供。
using type = volatile T;
```

## 约束说明

- 提供特征类以及标准的 _t、_v辅助形式。

## 调用示例

以下Host示例使用独立的预期类型或值检查接口结果。

```cpp
#include <asc/std/type_traits>

using result_type = typename asc::std::add_volatile<int>::type;
static_assert(asc::std::is_same_v<result_type, volatile int>);
```

## 关联API

- [`asc::std::add_volatile`](add_volatile.md)
- [本头文件的接口列表](asc_std_type_traits.md)
