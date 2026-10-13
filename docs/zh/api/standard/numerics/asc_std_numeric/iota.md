# asc::std::iota

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

头文件路径为：`<asc/std/numeric>`。

`asc::std::iota`从给定起始值开始连续填充范围。

标准语义参考：[cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric)。

## 函数原型

```cpp
namespace asc::std {
template<class ForwardIterator, class T> constexpr void iota(ForwardIterator first, ForwardIterator last, T value_);
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ForwardIterator` | 待填充范围的迭代器类型；须可写入所指元素并向后遍历。 |
| `T` | 填充起始值与范围元素的类型；须支持 ++ 自增。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 待填充范围的起始迭代器。 |
| `last` | 输入 | 待填充范围的尾后迭代器，不包含该位置。 |
| `value_` | 输入 | 填充的起始值；写入首元素后每前进一步自增一次，继续写入后续元素。 |

## 返回值说明

无返回值。

## 约束说明

- 提供顺序迭代器/值重载。
- 本族中标准定义的执行策略重载采用顺序执行语义。

## 调用示例

以下片段用具体整数范围展示数值调用；输出数组具有足够容量。

```cpp
#include <asc/std/numeric>

void example()
{
    int output[4] = {};
    asc::std::iota(output, output + 4, 1);
}
```

## 关联API

- [本头文件的接口列表](asc_std_numeric.md)
