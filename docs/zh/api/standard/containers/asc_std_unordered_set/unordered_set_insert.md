# asc::std::unordered_set::insert

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

头文件路径为：`<asc/std/unordered_set>`。

`asc::std::unordered_set::insert`在指定位置插入元素并按容器规则更新迭代器。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `unordered_set`](https://en.cppreference.com/w/cpp/header/unordered_set)。

## 函数原型

所属类型：[`unordered_set`](unordered_set.md)。返回类型以auto作签名摘要：实际结果对象具有iterator类型的first与bool类型的second，不是asc::std::pair。

### 原型1

```cpp
auto insert(const Key& key);
```

### 原型2

```cpp
auto insert(Key&& key);
```

## 参数说明

### 原型1的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `key` | 输入 | 待插入键；键不存在时复制构造新元素，已存在时不插入。 |

### 原型2的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `key` | 输入 | 待插入键；键不存在时移动构造新元素，源对象可能被移动；已存在时不消耗来源。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `含first/second的结果对象` | first指向该键元素、second表示是否新插入；重复键时second为false。first借用容器，容器或元素销毁后不可继续使用。 |
| 原型2 | `含first/second的结果对象` | first指向该键元素、second表示是否新插入；重复键时second为false。first借用容器，容器或元素销毁后不可继续使用。 |

## 约束说明

- Host及AI Core SIMT编程下unordered_set<Key,Hash,Equal,A>显式GM arena。
- empty/size/bucket_count/begin/end/insert/find/count/clear。
- allocator回绑桶数组并在默认负载阈值上自动rehash。
- 碰撞链、重复键拒绝、rehash节点地址稳定、移动后旧迭代器有效与析构。
- 仅容量充足和不抛出异常域。
- Host和AI Core SIMT编程。
- 本操作使用容器选定的`Hash`及`Equal`定位键；等价键必须产生相同哈希，且键相关状态须保持有效。自定义键、忽略字段和对象字节回退的要求见[unordered_set约束](unordered_set.md)。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/unordered_set>
#include <functional>
#include <memory>
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

bool example()
{
    using set_type = asc::std::unordered_set<int, ::std::hash<int>, ::std::equal_to<int>, example_allocator<int>>;
    set_type values{example_allocator<int>{}};
    const auto inserted = values.insert(7);
    const auto duplicate = values.insert(7);
    return inserted.second && !duplicate.second && *inserted.first == 7 && values.size() == 1;
}
```

## 关联API

- [`asc::std::unordered_set`](unordered_set.md)
- [本头文件的接口列表](asc_std_unordered_set.md)
