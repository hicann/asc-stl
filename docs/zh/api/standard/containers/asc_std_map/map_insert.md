# asc::std::map::insert

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

`asc::std::map::insert`在指定位置插入元素并按容器规则更新迭代器。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `map`](https://en.cppreference.com/w/cpp/header/map)。

## 函数原型

所属类型：[`asc::std::map`](map.md)。

### 原型1

```cpp
// asc::std::map 类内的声明节选；模板形参和其他成员由所属类提供。
pair<iterator, bool> insert(const value_type& value);
```

### 原型2

```cpp
// asc::std::map 类内的声明节选；模板形参和其他成员由所属类提供。
pair<iterator, bool> insert(value_type&& value);
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待插入的键值对（value_type为pair<const Key, T>）；键不存在时复制构造新元素，键已存在时不插入。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待插入的键值对；键不存在时以移动方式构造新元素，键已存在时不插入且源对象不被消耗。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `pair<iterator, bool>` | 返回指向该键元素的迭代器及是否新插入的bool；键已存在时bool为false。 |
| 原型2 | `pair<iterator, bool>` | 返回指向该键元素的迭代器及是否新插入的bool；键已存在时bool为false。 |

## 约束说明

- Host及AI Core SIMT编程下map<Key,T,Compare,A>显式GM arena。
- allocator以及Compare+allocator构造。
- empty/size/begin/end/insert/find/count/`operator[]`/clear。
- AVL平衡与对数级插入/查找核心。
- 重复键拒绝、有序迭代、移动和析构。
- 仅容量充足和不抛出异常键值/比较/allocator域。
- Host和AI Core SIMT编程。

## 调用示例

以下Host片段使用显式提供的分配器；设备端须使用在目标执行位置可调用的分配器。

```cpp
#include <asc/std/map>
#include <functional>
#include <memory>
#include <string>
#include <utility>

template <class T>
struct example_allocator : ::std::allocator<T> {
    using value_type = T;
    using pointer = T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template <class U> struct rebind { using other = example_allocator<U>; };
    example_allocator() = default;
    template <class U> example_allocator(const example_allocator<U>&) noexcept {}
};

decltype(auto) example(asc::std::map<int, int, ::std::less<int>, example_allocator<::std::pair<const int, int>>>& values)
{
    using entry_type = asc::std::map<int, int, ::std::less<int>, example_allocator<::std::pair<const int, int>>>::value_type;
    entry_type entry(7, 9);
    return values.insert(entry);
}
```

## 关联API

- [`asc::std::map`](map.md)
- [本头文件的接口列表](asc_std_map.md)
