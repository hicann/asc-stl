# asc::std::inplace_vector::erase

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

头文件路径为：`<asc/std/inplace_vector>`。

`asc::std::inplace_vector::erase` 按目标值从固定容量容器中移除元素并返回删除数量。

该接口的可用位置为 Host（完整接口）、Device（非抛出子集）。

标准语义参考：[cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector)。

## 函数原型

### 原型 1

```cpp
iterator asc::std::inplace_vector::erase(const_iterator position);
```

### 原型 2

```cpp
iterator asc::std::inplace_vector::erase(const_iterator first, const_iterator last);
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `position` | 输入 | 指向本次操作位置的迭代器；所指范围须在调用期间有效。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `iterator` | 返回删除数量。 |
| 原型 2 | `iterator` | 返回删除数量。 |

## 约束说明

- 最终C++26标准inplace_vector/erase/erase_if合同：Host交付除P4022R0已删除try_append_range外的完整构造、赋值、迭代、访问、修改、try/unchecked、比较、swap、容量、零容量empty/trivial与constexpr/约束合同
- Device交付固定容量内联存储的非抛子合同，包括观察/迭代/operator[]/front/back、不抛出异常拷移赋值析构、try/unchecked后插、pop_back/clear、不抛出异常 erase/erase_if/swap、相等与不抛出异常三路比较、完整零容量核心
- Host 提供完整接口，设备端仅提供不抛出异常的接口

## 调用示例

以下 Host 片段以具体容量或维度演示调用；对象和索引须满足本页约束。

```cpp
#include <asc/std/inplace_vector>

decltype(auto) example(asc::std::inplace_vector<int, 8>& values)
{
    if (!values.empty())
        return values.erase(values.begin());
}
```
