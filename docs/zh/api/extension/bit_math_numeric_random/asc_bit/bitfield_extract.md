# asc::bitfield_extract

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

头文件路径为：`<asc/bit>`。

`asc::bitfield_extract`从无符号整数的`start`位开始提取连续`width`位，并将结果右对齐返回。

## 函数原型

```cpp
namespace asc {
template <class T>
constexpr T bitfield_extract(T value, int start, int width) noexcept;
}  // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 与 `asc::std::uint32_t` 或 `asc::std::uint64_t` 相同的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待提取位域的无符号整数值。 |
| `start` | 输入 | 位域在`value`中的起始位编号（最低位为第0位）；非法参数结果见约束说明。 |
| `width` | 输入 | 待提取的连续位数；非法参数结果见约束说明。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回从指定起始位提取并右对齐的位域值。 |

## 约束说明

- `T` 必须与 `asc::std::uint32_t` 或 `asc::std::uint64_t` 为同一类型；同型别名可匹配，仅位宽相同的另一种类型不自动匹配。不满足条件时不参与重载决议。
- 按值推导去掉实参的顶层 cv 限定；显式指定 cv/ref 类型不满足类型约束。
- 支持 C++17/C++20、Host、SIMT 线程和 SIMD 核内的普通标量代码。常量求值与运行时结果一致，函数不抛出异常。
- 最低有效位为第 0 位，按整数值编号，与内存字节序或 C++ 位域成员布局无关。
- 设位宽为 `W`，合法区间满足 `0 <= start && start <= W && 0 <= width && width <= W - start`。
- 合法非空区间 `[start, start + width)` 右对齐返回，高位补零。
- 零宽（包括 `(W, 0)`）或非法区间返回 `T{0}`；`(0, W)` 返回原值。最高位窗口 `(W - 1, 1)` 合法。
- 负数、参数超过位宽或区间越界均按非法区间处理，包括任意 `int` 极值；不截短区间或对参数取模。

## 调用示例

```cpp
#include <asc/bit>
#include <asc/std/cstdint>

using u32 = asc::std::uint32_t;
constexpr auto field = asc::bitfield_extract(u32{0xA5A50AB0}, 4, 8);
static_assert(field == u32{0xAB});
static_assert(asc::bitfield_extract(u32{1}, 32, 0) == u32{0});

bool verify_example()
{
    return asc::bitfield_extract(u32{0xFFFFFFFF}, 31, 2) == u32{0};
}
```

## 关联API

- [本头文件的接口列表](asc_bit.md)
