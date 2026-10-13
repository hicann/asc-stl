# asc::std::map::map

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

`asc::std::map::map`按本页所列构造形态初始化`map`对象。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `map`](https://en.cppreference.com/w/cpp/header/map)。

## 函数原型

### 原型1

```cpp
map(const Allocator& allocator);
```

### 原型2

```cpp
map(const Compare& compare, const Allocator& allocator);
```

### 原型3

```cpp
map(map<Key, T, Compare, Allocator>&& other) noexcept;
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `compare` | 输入 | 用于确定元素顺序的比较对象。 |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 构造来源对象；本对象由其对应成员或底层状态初始化，右值形式可移动该状态。 |

## 返回值说明

无返回值。

## 约束说明

- Host及AI Core SIMT编程下map<Key,T,Compare,A>显式GM arena。
- allocator以及Compare+allocator构造。
- empty/size/begin/end/insert/find/count/`operator[]`/clear。
- AVL平衡与对数级插入/查找核心。
- 重复键拒绝、有序迭代、移动和析构。
- 仅容量充足和不抛出异常键值/比较/allocator域。
- Host和AI Core SIMT编程。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

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
    values[1] = 7;
    values[3] = 9;
    return values.size() == 2;
}
```

## 关联API

- [本头文件的接口列表](asc_std_map.md)
