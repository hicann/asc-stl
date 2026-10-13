# asc::std::deque::empty

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

头文件路径为：`<asc/std/deque>`。

`asc::std::deque::empty`判断当前对象是否不含元素。

标准语义参考：[cppreference `deque`](https://en.cppreference.com/w/cpp/header/deque)。

## 函数原型

所属类型：[`asc::std::deque`](deque.md)。

```cpp
// asc::std::deque 类内的声明节选；模板形参和其他成员由所属类提供。
bool empty() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 对象不含元素时返回`true`，否则返回`false`。 |

## 约束说明

- deque<T,A>显式allocator构造。
- 有限块映射内的push/emplace/pop_front/back。
- empty/size/front/back/`operator[]`/随机访问迭代核心。
- 新端块分配时已有元素引用稳定。
- clear/析构。
- 仅容量充足和不抛出异常域。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/memory>
#include <asc/std/deque>

bool example()
{
    alignas(64) unsigned char storage[16384] = {};
    asc::monotonic_arena arena(storage, sizeof(storage));
    asc::std::deque<int, asc::arena_allocator<int>> values(asc::arena_allocator<int>{arena});
    values.push_back(1);
    values.push_back(3);
    return !values.empty();
}
```

## 关联API

- [`asc::std::deque`](deque.md)
- [本头文件的接口列表](asc_std_deque.md)
