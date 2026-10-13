# asc::make_strided_iterator

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

头文件路径为：`<asc/iterator>`。

`asc::make_strided_iterator`从底层随机访问迭代器构造定步长适配器；单参数重载使用步长1，双参数重载使用给定的正或负非零步长。

## 函数原型

### 原型1

```cpp
namespace asc {
template<class Iterator, class Stride> constexpr asc::strided_iterator<Iterator, Stride> make_strided_iterator(Iterator iterator, Stride stride);
} // namespace asc
```

### 原型2

```cpp
namespace asc {
template<class Iterator> constexpr asc::strided_iterator<Iterator> make_strided_iterator(Iterator iterator);
} // namespace asc
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Iterator` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `Stride` | 步长类型（整数）。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `iterator` | 输入 | 被包装的底层迭代器：本迭代器每前进1步，底层迭代器前进stride个位置。 |
| `stride` | 输入 | 每步跨越的底层元素个数：前进/后退1步对应底层迭代器移动stride个位置，须非零。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Iterator` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `iterator` | 输入 | 被包装的底层迭代器：该原型为步长1的退化形式，按单位步长访问。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `asc::strided_iterator<Iterator, Stride>` | 返回保存调用方参数的迭代器适配器；底层范围须在使用期间保持有效。 |
| 原型2 | `asc::strided_iterator<Iterator>` | 返回保存调用方参数的迭代器适配器；底层范围须在使用期间保持有效。 |

## 约束说明

- 底层迭代器须支持随机访问，步长须为非零整数。
- 返回对象不拥有底层范围。
- 提供惰性、非拥有的迭代器适配器及其工厂。
- 操作数必须在当前执行位置有效。

## 调用示例

以下片段使用具体数组和可调用对象构造迭代器。实际使用时底层范围须保持有效。

```cpp
#include <asc/iterator>

decltype(auto) example()
{
    int values[4] = {1, 2, 3, 4};
    int indices[4] = {3, 2, 1, 0};
    return asc::make_strided_iterator(values, 2);
}
```

## 关联API

- [本头文件的接口列表](asc_iterator.md)
