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
| `T` | 填充起始值的类型；递增后须能赋值给范围元素，二者类型可以不同；须支持 ++ 自增。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 待填充范围的起始迭代器。 |
| `last` | 输入 | 待填充范围的尾后迭代器，不包含该位置。 |
| `value_` | 输入 | 填充的起始值；写入首元素后每前进一步自增一次，继续写入后续元素。 |

## 返回值说明

无返回值。

## 约束说明

- `[first, last)`须为有效的可写前向迭代范围。
- 每次将当前`value`赋给一个元素后执行`++value`；类型须支持赋值和前置递增，所需递增操作须有效。

## 调用示例

以下示例将四个输出元素依次填为1、2、3、4。

```cpp
#include <asc/std/numeric>

bool example()
{
    int output[4] = {};
    asc::std::iota(output, output + 4, 1);
    return output[0] == 1 && output[1] == 2 && output[2] == 3 && output[3] == 4;
}
```

## 关联API

- [本头文件的接口列表](asc_std_numeric.md)
