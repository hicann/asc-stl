# asc::std::stack::value_type

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

头文件路径为：`<asc/std/stack>`。

`asc::std::stack::value_type`标识元素或结果的值类型。

标准语义参考：[cppreference `stack`](https://en.cppreference.com/w/cpp/header/stack)。

## 声明

所属类型：[`asc::std::stack`](stack.md)。

```cpp
// asc::std::stack 类内的声明节选；模板形参和其他成员由所属类提供。
using value_type = typename Container::value_type;
```

## 约束说明

- 该别名取自选定的Container或Compare；别名查询本身不构造容器或调用比较器。

## 调用示例

以下Host片段显式提供标准容器作为底层存储；设备端须提供可在目标位置调用的容器。

```cpp
#include <asc/std/stack>
#include <deque>
#include <functional>
#include <vector>

void use_type()
{
    using alias_type = typename asc::std::stack<int, ::std::deque<int>>::value_type;
}
```

## 关联API

- [`asc::std::stack`](stack.md)
- [本头文件的接口列表](asc_std_stack.md)
