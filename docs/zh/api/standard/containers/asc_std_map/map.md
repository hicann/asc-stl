# asc::std::map

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

头文件路径为：`<asc/std/map>`。

`asc::std::map`按键的比较顺序保存键值对。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `map`](https://en.cppreference.com/w/cpp/header/map)。

## 声明

```cpp
namespace asc::std {
template<class Key, class T, class Compare, class Allocator> class map;
} // namespace asc::std
```

## 约束说明

- Host及AI Core SIMT编程下map<Key,T,Compare,A>显式GM arena。
- allocator以及Compare+allocator构造。
- empty/size/begin/end/insert/find/count/`operator[]`/clear。
- AVL平衡与对数级插入/查找核心。
- 重复键拒绝、有序迭代、移动和析构。
- 仅容量充足和不抛出异常键值/比较/allocator域。
- Host和AI Core SIMT编程。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/memory>
#include <functional>
#include <asc/std/map>
#include <asc/std/utility>

bool example()
{
    alignas(64) unsigned char storage[16384] = {};
    asc::monotonic_arena arena(storage, sizeof(storage));
    using allocator = asc::arena_allocator<asc::std::pair<const int, int>>;
    asc::std::map<int, int, ::std::less<int>, allocator> values(allocator{arena});
    values[2] = 7;
    return values.size() == 1 && values[2] == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_map.md)
