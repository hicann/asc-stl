# asc::std::move_sentinel::move_sentinel

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

头文件路径为：`<asc/std/iterator>`。

`asc::std::move_sentinel::move_sentinel`按本页所列构造形态初始化`move_sentinel`对象。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

所属类型：[`move_sentinel<Sent>`](move_sentinel.md)。以下为C++17及Device的选择形式；Host C++20对转换构造使用相同的convertible_to条件。

### 原型1

```cpp
constexpr move_sentinel() = default;
```

### 原型2

```cpp
constexpr explicit move_sentinel(Sent sentinel);
```

### 原型3

```cpp
template<class S2, enable_if_t<convertible_to<const S2&, Sent>, int> = 0>
constexpr move_sentinel(const move_sentinel<S2>& other);
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `sentinel` | 输入 | 被包装的哨兵；新对象保存其副本，用于与move_iterator比较以判定范围结束。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `S2` | 来源move_sentinel的哨兵类型；const S2&须满足convertible_to<const S2&, Sent>，包括隐式转换要求。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 复制来源move_sentinel；新对象保存其哨兵的副本。 |

## 返回值说明

无返回值。

## 约束说明

- 哨兵类型须支持对应构造、转换或赋值操作，并可与配套底层迭代器比较。
- 哨兵不拥有底层范围，也不能解引用；其结束标记须在比较期间有效。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>
#include <asc/std/type_traits>

bool example()
{
    int values[] = {2, 4};
    asc::std::move_sentinel<int*> empty;
    asc::std::move_sentinel<int*> direct(values + 2);
    asc::std::move_sentinel<const int*> converted(direct);
    static_assert(!asc::std::is_convertible_v<int*, asc::std::move_sentinel<int*>>);
    return empty.base() == nullptr && converted.base() == values + 2;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
