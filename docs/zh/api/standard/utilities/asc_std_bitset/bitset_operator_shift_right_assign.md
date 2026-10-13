# asc::std::bitset::operator>>=

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

`asc::std::bitset::operator>>=` 按 `bitset` 的可用运算符规则处理当前对象及操作数。

标准语义参考：[cppreference `bitset`](https://en.cppreference.com/w/cpp/header/bitset)。

## 函数原型

```cpp
bitset<Size>& asc::std::bitset::operator>>=(size_t shift) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `shift` | 输入 | 右移的位数；移出的低位丢弃、空出的高位补 0，不小于 Size 时结果全为 0。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bitset<Size> &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |

## 约束说明

- 支持默认构造和 unsigned long long 构造
- operator[] 不进行边界检查
- 提供整组 set、reset、flip，位运算、移位、状态检查、计数和容量查询

## 调用示例

以下 Host 片段以 8 位 bitset 演示具体调用；索引须在有效范围内。

```cpp
#include <asc/std/bitset>

decltype(auto) example(asc::std::bitset<8>& bits)
{
    return (bits >>= 1);
}
```
