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

`asc::std::move_sentinel::move_sentinel` 按本页所列构造形态初始化 `move_sentinel` 对象。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

### 原型 1

```cpp
constexpr move_sentinel();
```

### 原型 2

```cpp
constexpr move_sentinel(Sent sentinel);
```

### 原型 3

```cpp
template<class S2> constexpr move_sentinel(const move_sentinel<S2>& other);
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `sentinel` | 输入 | 被包装的哨兵；新对象保存其副本，用于与 move_iterator 比较以判定范围结束。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `S2` | 来源 move_sentinel 的哨兵类型；其哨兵须能转换构造为本类型的哨兵。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 复制来源 move_sentinel；新对象保存其哨兵的副本。 |

## 约束说明

- 使用调用方提供的迭代器或容器
- 关系运算符均为显式提供

## 调用示例

以下 Host 片段以具体指针迭代器演示调用；调用方须保证所指范围及移动后位置有效。

```cpp
#include <asc/std/iterator>

void example()
{
    asc::std::move_sentinel<int*> iterator{};
    (void)iterator;
}
```
