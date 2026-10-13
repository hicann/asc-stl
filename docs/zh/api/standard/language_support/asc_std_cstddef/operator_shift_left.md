# asc::std::operator<<

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

`asc::std::operator<<` 将 `lhs` 所含 std::byte 的整数值向左移动 `shift` 位，移位结果以 `byte` 返回。`shift` 须为非负整数，有效移位范围为 0 <= s < 8（以实现为准）。

标准语义参考：[cppreference `cstddef`](https://en.cppreference.com/w/cpp/header/cstddef)。

## 函数原型

```cpp
template<class Integer> constexpr byte asc::std::operator<<(byte lhs, Integer shift) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Integer` | 移位位数的整数类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `lhs` | 输入 | 参与左移的 byte 操作数；按其底层 unsigned char 位左移。 |
| `shift` | 输入 | 左移的位数。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `byte` | 返回 `lhs` 的整数值左移 `shift` 位后得到的 `byte` 值。 |

## 约束说明

- 提供标准声明

## 调用示例

以下片段用具体对象展示本页调用。

```cpp
#include <asc/std/cstddef>

decltype(auto) example()
{
    asc::std::byte value{1};
    return asc::std::operator<<(value, 2);
}
```
