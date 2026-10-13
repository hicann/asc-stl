# asc::std::set::empty

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

头文件路径为：`<asc/std/set>`。

`asc::std::set::empty`判断当前对象是否不含元素。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `set`](https://en.cppreference.com/w/cpp/header/set)。

## 函数原型

所属类型：[`asc::std::set`](set.md)。

```cpp
// asc::std::set 类内的声明节选；模板形参和其他成员由所属类提供。
bool empty() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 对象不含元素时返回`true`，否则返回`false`。 |

## 约束说明

- Host及AI Core SIMT编程下set<Key,Compare,A>显式GM arena。
- allocator以及Compare+allocator构造。
- empty/size/begin/end/insert/find/count/clear。
- AVL平衡与对数级插入/查找核心。
- 重复键拒绝、有序迭代、移动和析构。
- 仅容量充足和不抛出异常键/比较/allocator域。
- Host和AI Core SIMT编程。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/memory>
#include <functional>
#include <asc/std/set>

bool example()
{
    alignas(64) unsigned char storage[16384] = {};
    asc::monotonic_arena arena(storage, sizeof(storage));
    asc::std::set<int, ::std::less<int>, asc::arena_allocator<int>> values(asc::arena_allocator<int>{arena});
    values.insert(1);
    values.insert(3);
    values.insert(3);
    return !values.empty();
}
```

## 关联API

- [`asc::std::set`](set.md)
- [本头文件的接口列表](asc_std_set.md)
