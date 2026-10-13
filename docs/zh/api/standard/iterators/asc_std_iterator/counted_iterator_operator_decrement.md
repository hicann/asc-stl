# asc::std::counted_iterator::`operator--`

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

`asc::std::counted_iterator::operator--`把当前迭代器或计数值后退一步。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

所属类型：[`asc::std::counted_iterator`](counted_iterator.md)。

### 原型1

```cpp
// asc::std::counted_iterator 类内的声明节选；模板形参和其他成员由所属类提供。
template<class I2> constexpr counted_iterator<Iter>& operator--();
```

### 原型2

```cpp
// asc::std::counted_iterator 类内的声明节选；模板形参和其他成员由所属类提供。
template<class I2> constexpr counted_iterator<Iter> operator--(int unused);
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `I2` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `I2` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `unused` | 输入 | 用于区分后置自增或后置自减形式的占位参数；调用时写作整数0。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `counted_iterator<Iter> &` | 返回更新后的当前对象引用。 |
| 原型2 | `counted_iterator<Iter>` | 返回更新后的迭代器或计数值。 |

## 约束说明

- 使用调用方提供的迭代器或容器。
- pair的直接自由比较入口为`operator==`和`operator<`；其他关系辅助位于`rel_ops`。

## 调用示例

以下Host片段以具体指针迭代器演示调用；调用方须保证所指范围及移动后位置有效。

```cpp
#include <asc/std/iterator>

void example(asc::std::counted_iterator<int*>& iterator)
{
    --iterator;
}
```

## 关联API

- [`asc::std::counted_iterator`](counted_iterator.md)
- [本头文件的接口列表](asc_std_iterator.md)
