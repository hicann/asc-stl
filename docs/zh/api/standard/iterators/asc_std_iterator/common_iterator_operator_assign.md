# asc::std::common_iterator::`operator=`

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

`asc::std::common_iterator::operator=`按所选赋值重载更新对象，并返回规定的结果。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

所属类型：[`asc::std::common_iterator`](common_iterator.md)。

### 原型1

```cpp
// asc::std::common_iterator 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr common_iterator<Iter, Sent>& operator=(common_iterator<Iter, Sent>&& other);
```

### 原型2

```cpp
// asc::std::common_iterator 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr common_iterator<Iter, Sent>& operator=(const common_iterator<Iter, Sent>& other);
```

### 原型3

```cpp
// asc::std::common_iterator 类内的声明节选；模板形参和其他成员由所属类提供。
template<class I2, class S2> constexpr common_iterator<Iter, Sent>& operator=(const common_iterator<I2, S2>& other);
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 赋值来源对象；左值形式复制其状态，右值形式按对应成员的移动操作转移状态。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 赋值来源对象；左值形式复制其状态，右值形式按对应成员的移动操作转移状态。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `I2` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `S2` | 来源哨兵的类型；须满足到当前哨兵类型的转换条件。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 赋值来源对象；左值形式复制其状态，右值形式按对应成员的移动操作转移状态。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `common_iterator<Iter, Sent> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型2 | `common_iterator<Iter, Sent> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型3 | `common_iterator<Iter, Sent> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

## 约束说明

- 使用调用方提供的迭代器或容器。
- pair的直接自由比较入口为`operator==`和`operator<`；其他关系辅助位于`rel_ops`。

## 调用示例

以下Host片段使用具体指针与哨兵演示调用；解引用前须保证指针有效。

```cpp
#include <asc/std/iterator>

void example(int* data)
{
    asc::std::common_iterator<int*, asc::std::unreachable_sentinel_t> iterator(data);
    asc::std::common_iterator<int*, asc::std::unreachable_sentinel_t> other(data);
    iterator = static_cast<asc::std::common_iterator<int*, asc::std::unreachable_sentinel_t>&&>(other);
}
```

## 关联API

- [`asc::std::common_iterator`](common_iterator.md)
- [本头文件的接口列表](asc_std_iterator.md)
