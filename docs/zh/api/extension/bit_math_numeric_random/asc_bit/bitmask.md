# asc::bitmask

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

`asc::bitmask`生成32位或64位无符号整数掩码，从`start`位开始将连续`width`位设置为1，其余位为0。

## 函数原型

```cpp
namespace asc {
template<class T = asc::std::uint32_t> constexpr T bitmask(int start, int width) noexcept;
} // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 掩码的无符号整数类型；须为uint32_t或uint64_t，省略时为uint32_t。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `start` | 输入 | 掩码的起始位编号（最低位为第0位）；不得为负。 |
| `width` | 输入 | 掩码中连续置1的位数，从`start`位向高位延伸；不得为负。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回32位或64位无符号整数掩码，从`start`位开始将连续`width`位设置为1，其余位为0。 |

## 约束说明

- T 必须为 uint32_t 或 uint64_t。
- start/width 越界（负值、超位宽或 start+width 越过类型位宽窗口）时钳制返回 T{0}，不再构成未定义行为；零位宽同样返回 T{0}，全位宽窗口正常生成全 1 掩码，任何合法输入都不产生未定义移位。

## 调用示例

以下片段选用具体整数实参展示接口调用。

```cpp
#include <asc/bit>

decltype(auto) example()
{
    return asc::bitmask<unsigned int>(2, 3);
}

bool verify_example()
{
    return example() == 28u;
}
```

## 关联API

- [本头文件的接口列表](asc_bit.md)
