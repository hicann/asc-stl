# asc::std::bitset::base

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

`asc::std::bitset::base`标识位集合采用的底层存储类型。

标准语义参考：[cppreference `bitset`](https://en.cppreference.com/w/cpp/header/bitset)。

## 声明

`asc::std::bitset<Size>::base`是当前实现公开的底层存储类型别名，具体类型属于实现细节，不应假定存在名为Bitset或Nwords的公共类型／参数。一般代码应使用bitset的公开成员。

```cpp
using Storage = asc::std::bitset<8>::base;
```

## 约束说明

- 所属bitset的位数Size在编译期固定，操作不进行动态分配。base是存储实现类型的公开别名；使用者通常通过bitset的公开成员操作位。

## 调用示例

以下Host示例用具体类型和独立预期检查别名或标记结果。

```cpp
#include <asc/std/bitset>
#include <asc/std/type_traits>

void use_type()
{
    using alias_type = typename asc::std::bitset<8>::base;
    static_assert(asc::std::is_base_of_v<alias_type, asc::std::bitset<8>>);
}
```

## 关联API

- [本头文件的接口列表](asc_std_bitset.md)
