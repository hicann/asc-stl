# asc::bit_reverse

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

`asc::bit_reverse`反转32位或64位无符号整数的全部二进制位，使最低位与最高位、次低位与次高位依次交换。

## 函数原型

```cpp
namespace asc {
template <class T>
constexpr T bit_reverse(T value) noexcept;
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
| `value` | 输入 | 待反转全部二进制位的无符号整数值。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回所有二进制位逆序排列后的整数。 |

## 约束说明

- `T` 必须与 `asc::std::uint32_t` 或 `asc::std::uint64_t` 为同一类型；同型别名可匹配，仅位宽相同的另一种类型不自动匹配。不满足条件时不参与重载决议。
- 按值推导去掉实参的顶层 cv 限定；显式指定 cv/ref 类型不满足类型约束。
- 支持 C++17/C++20、Host、SIMT 线程和 SIMD 核内的普通标量代码。常量求值与运行时结果一致，函数不抛出异常。
- 设位宽为 `W`，结果第 `W - 1 - i` 位等于输入第 `i` 位。零和全一保持原值。
- 全位反转镜像每个位的位置；字节交换按字节排列，循环移位保持位的循环次序。

## 调用示例

```cpp
#include <asc/bit>
#include <asc/std/cstdint>

using u32 = asc::std::uint32_t;
using u64 = asc::std::uint64_t;
static_assert(asc::bit_reverse(u32{0x0000000D}) == u32{0xB0000000});

bool verify_example()
{
    return asc::bit_reverse(u64{1}) == u64{0x8000000000000000};
}
```

## 关联API

- [本头文件的接口列表](asc_bit.md)
