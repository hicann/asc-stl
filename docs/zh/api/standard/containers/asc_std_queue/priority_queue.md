# asc::std::priority_queue

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

`asc::std::priority_queue`按比较优先级访问底层容器。

标准语义参考：[cppreference `queue`](https://en.cppreference.com/w/cpp/header/queue)。

## 声明

```cpp
namespace asc::std {
template<class T, class Container, class Compare> class priority_queue;
} // namespace asc::std
```

## 约束说明

- 显式指定T与Container，且T与Container::value_type一致。
- 第三个模板实参Compare可省略，默认比较等价于元素的小于比较，堆顶为最大元素；其准确类型通过value_compare查询，不假定等同于asc::std::less。
- 不提供独立allocator构造、uses_allocator特化、比较运算符或显式推导指引。
- Device使用的Container、元素操作及Compare须可在对应执行位置调用并满足其非抛出要求；Host的异常行为遵循所调用对象，未额外声明noexcept时不承诺不抛出。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <vector>
#include <functional>
#include <asc/std/queue>

bool example()
{
    asc::std::priority_queue<int, ::std::vector<int>, ::std::less<int>> values;
    values.push(1);
    values.push(3);
    values.push(2);
    return values.size() == 3 && values.top() == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_queue.md)
