# asc::std::priority_queue::swap

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

`asc::std::priority_queue::swap`交换两个对象保存的状态或元素。

标准语义参考：[cppreference `queue`](https://en.cppreference.com/w/cpp/header/queue)。

## 函数原型

所属类型：[`priority_queue<T, Container, Compare>`](priority_queue.md)。本成员没有noexcept规格。

```cpp
constexpr void swap(priority_queue& other);
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 与当前对象交换状态的另一对象；交换后双方保存对方原有状态。 |

## 返回值说明

无返回值。

## 约束说明

- Container须支持swap；priority_queue还移动交换Compare。
- Device使用的Container、元素操作及Compare须可在对应执行位置调用并满足其非抛出要求；Host的异常行为遵循所调用对象，未额外声明noexcept时不承诺不抛出。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/queue>
#include <functional>
#include <vector>

bool example()
{
    using queue_type = asc::std::priority_queue<int, ::std::vector<int>, ::std::less<int>>;
    queue_type first;
    queue_type second;
    first.push(3);
    second.push(1);
    static_assert(!noexcept(first.swap(second)));
    first.swap(second);
    return first.top() == 1 && second.top() == 3;
}
```

## 关联API

- [`asc::std::priority_queue`](priority_queue.md)
- [本头文件的接口列表](asc_std_queue.md)
