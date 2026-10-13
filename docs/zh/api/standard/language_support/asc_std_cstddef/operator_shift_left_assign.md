# `asc::std::operator<<=`

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

头文件路径为：`<asc/std/cstddef>`。

`asc::std::operator<<=`将`lhs`所含std::byte的整数值向左移动`shift`位，把移位结果存回`lhs`并返回其引用。`shift`须为非负整数，移位量须小于`unsigned int`的位宽；运算先将字节值提升为`unsigned int`，移位后再转换为`byte`。

标准语义参考：[cppreference `cstddef`](https://en.cppreference.com/w/cpp/header/cstddef)。

## 函数原型

```cpp
namespace asc::std {
template<class Integer> constexpr byte& operator<<=(byte& lhs, Integer shift) noexcept;
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Integer` | 移位位数的整数类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `lhs` | 输入/输出 | 被左移更新的byte对象；按其底层unsigned char位左移shift位，返回其引用。 |
| `shift` | 输入 | 左移的位数。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `byte &` | 返回存回左移结果后的`lhs`引用，可继续进行赋值或复合操作。 |

## 约束说明

- 提供标准声明。

## 调用示例

以下片段用具体对象展示本页调用。

```cpp
#include <asc/std/cstddef>

decltype(auto) example()
{
    asc::std::byte value{1};
    return asc::std::operator<<=(value, 2);
}
```

## 关联API

- [本头文件的接口列表](asc_std_cstddef.md)
