# asc::std::priority_queue::push

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

头文件路径为：`<asc/std/queue>`。

`asc::std::priority_queue::push`向容器适配器插入一个元素。

标准语义参考：[cppreference `queue`](https://en.cppreference.com/w/cpp/header/queue)。

## 函数原型

所属类型：[`asc::std::priority_queue`](priority_queue.md)。

### 原型1

```cpp
// asc::std::priority_queue 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr void push(const value_type& value);
```

### 原型2

```cpp
// asc::std::priority_queue 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr void push(value_type&& value);
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待插入的元素值；以复制方式插入底层容器，并按容器的比较关系调整到满足优先级的位置。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待插入的元素值；以移动方式插入底层容器并按比较关系调整位置，插入后源对象处于有效但未指定的移后状态。 |

## 返回值说明

无返回值。

## 约束说明

- Container须支持所用的push_back或emplace_back；容量和元素构造要求遵循Container。
- Compare须保持严格弱序；插入后重新调整堆序。
- Device使用的Container、元素操作及Compare须可在对应执行位置调用并满足其非抛出要求；Host的异常行为遵循所调用对象，未额外声明noexcept时不承诺不抛出。

## 调用示例

以下Host片段显式提供标准容器作为底层存储；设备端须提供可在目标位置调用的容器。

```cpp
#include <asc/std/queue>
#include <deque>
#include <functional>
#include <vector>

void example(asc::std::priority_queue<int, ::std::vector<int>, ::std::less<int>>& object)
{
    object.push(7);
}
```

## 关联API

- [`asc::std::priority_queue`](priority_queue.md)
- [本头文件的接口列表](asc_std_queue.md)
