# asc::std::endian

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

头文件路径为：`<asc/std/bit>`。

`asc::std::endian`列出大端、小端与本机字节序标签。

标准语义参考：[cppreference `bit`](https://en.cppreference.com/w/cpp/header/bit)。

## 声明

```cpp
namespace asc::std {
enum endian;
} // namespace asc::std
```

## 约束说明

- `endian::native`与`endian::little`或`endian::big`之一相等，不支持混合字节序。
- 本产品宿主与设备环境均为小端，即`endian::native == endian::little`。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/bit>

bool example()
{
    static_assert(asc::std::endian::little != asc::std::endian::big);
    // 当前支持的Host和Device使用纯大端或纯小端字节序。
    return asc::std::endian::native == asc::std::endian::little || asc::std::endian::native == asc::std::endian::big;
}
```

## 关联API

- [本头文件的接口列表](asc_std_bit.md)
