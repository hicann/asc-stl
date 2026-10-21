# asc::std::bitset::operator&=

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

头文件路径为：`<asc/std/bitset>`。

`asc::std::bitset::operator&=`按`bitset`的可用运算符规则处理当前对象及操作数。

标准语义参考：[cppreference `bitset`](https://en.cppreference.com/w/cpp/header/bitset)。

## 函数原型

所属类型：[`asc::std::bitset`](bitset.md)。

```cpp
// asc::std::bitset 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr bitset<Size>& operator&=(const bitset<Size>& other) noexcept;
```


## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 按位运算的另一侧bitset；对应位分别参与与、或或异或，本操作不修改other。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bitset<Size> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

## 约束说明

- 所属bitset的位数Size在编译期固定，操作不进行动态分配。两个操作数须具有相同Size；二元按位操作逐位组合，不涉及构造来源状态。

## 调用示例

以下Host片段以8位bitset演示具体调用；索引须在有效范围内。

```cpp
#include <asc/std/bitset>

decltype(auto) example(asc::std::bitset<8>& left, const asc::std::bitset<8>& right)
{
    return (left &= right);
}
```

## 关联API

- [`asc::std::bitset`](bitset.md)
- [本头文件的接口列表](asc_std_bitset.md)
