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

`asc::bitmask` 生成 32 位或 64 位无符号整数掩码，从 `start` 位开始将连续 `width` 位设置为 1，其余位为 0。

## 函数原型

```cpp
template<class T = asc::std::uint32_t> constexpr T asc::bitmask(int start, int width) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 掩码的无符号整数类型；须为 uint32_t 或 uint64_t，省略时为 uint32_t。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `start` | 输入 | 掩码的起始位编号（最低位为第 0 位）；不得为负。 |
| `width` | 输入 | 掩码中连续置 1 的位数，从 `start` 位向高位延伸；不得为负。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回 32 位或 64 位无符号整数掩码，从 `start` 位开始将连续 `width` 位设置为 1，其余位为 0。 |

## 约束说明

- T 必须为 uint32_t 或 uint64_t
- start 和 width 不得为负且不得超出类型位宽，零位宽和全位宽操作不得产生未定义移位

## 调用示例

以下片段选用具体整数实参展示接口调用。

```cpp
#include <asc/bit>

decltype(auto) example()
{
    return asc::bitmask<unsigned int>(2, 3);
}
```
