# asc::std::bitset::reference

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

`asc::std::bitset::reference`标识可写元素引用类型。

标准语义参考：[cppreference `bitset`](https://en.cppreference.com/w/cpp/header/bitset)。

## 声明

所属类型：[`asc::std::bitset`](bitset.md)。

```cpp
// asc::std::bitset 类内的声明节选；模板形参和其他成员由所属类提供。
using reference = typename base::reference;
```

## 约束说明

- 所属bitset的位数Size在编译期固定，操作不进行动态分配。reference是可写位代理而非bool&，依赖原对象；const_reference是按值返回的bool。

## 调用示例

以下Host示例在被引用对象仍存活时检查结果。

```cpp
#include <asc/std/bitset>
#include <asc/std/type_traits>

bool example()
{
    asc::std::bitset<8> bits;
    using proxy = typename asc::std::bitset<8>::reference;
    proxy selected = bits[2];
    selected = true;
    if (!bits[2]) return false;
    selected.flip();
    return !bits[2];
}
```

## 关联API

- [`asc::std::bitset`](bitset.md)
- [本头文件的接口列表](asc_std_bitset.md)
