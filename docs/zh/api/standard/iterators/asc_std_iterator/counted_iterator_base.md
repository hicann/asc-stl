# asc::std::counted_iterator::base

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

`asc::std::counted_iterator::base` 返回适配器保存的底层迭代器或对象。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

### 原型 1

```cpp
[[nodiscard]] constexpr Iter asc::std::counted_iterator::base()&&;
```

### 原型 2

```cpp
[[nodiscard]] constexpr const Iter& asc::std::counted_iterator::base() const& noexcept;
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

无参数。

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `Iter` | 返回适配器保存的底层迭代器或对象。 |
| 原型 2 | `const Iter &` | 返回适配器保存的底层迭代器或对象。 |

## 约束说明

- 使用调用方提供的迭代器或容器
- 关系运算符均为显式提供

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/iterator>

void example(asc::std::counted_iterator<int*>& object)
{
    (void)object.base();
}
```
