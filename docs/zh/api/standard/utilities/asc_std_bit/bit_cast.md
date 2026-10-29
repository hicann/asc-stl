# asc::std::bit_cast

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

`asc::std::bit_cast`在满足大小和可平凡复制约束时复制对象表示并得到目标类型值。

标准语义参考：[cppreference `bit`](https://en.cppreference.com/w/cpp/header/bit)。

## 函数原型

```cpp
namespace asc::std {
template<class To, class From> [[nodiscard]] constexpr To bit_cast(const From& fx) noexcept;
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `To` | 位转换的目标类型；须可平凡复制且与来源类型大小相同。 |
| `From` | 位转换的来源类型；须可平凡复制且与目标类型大小相同。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `fx` | 输入 | 提供“在满足大小和可平凡复制约束时复制对象表示并得到目标类型值”使用的对象引用；被引用对象须在调用期间有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `To` | 返回对象表示相同、类型为目标类型的新值。 |

## 约束说明

- `To`与`From`须满足`sizeof(To) == sizeof(From)`且均为可平凡复制类型。
- 编译器提供`__builtin_bit_cast`时调用可用于常量表达式；否则经`memcpy`回退实现，此时`To`须可默认构造。

## 调用示例

以下片段用具体数值展示本页调用。

```cpp
#include <asc/std/bit>

decltype(auto) example()
{
    return asc::std::bit_cast<unsigned int>(1.0f);
}

bool verify_example()
{
    return example() == 0x3f800000u;
}
```

## 关联API

- [本头文件的接口列表](asc_std_bit.md)
