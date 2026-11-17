# asc::std::bitset::bitset

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

`asc::std::bitset::bitset`按本页所列构造形态初始化`bitset`对象。

标准语义参考：[cppreference `bitset`](https://en.cppreference.com/w/cpp/header/bitset)。

## 函数原型

### 原型1

```cpp
constexpr bitset() noexcept;
```

### 原型2

```cpp
constexpr bitset(unsigned long long value) noexcept;
```


## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 初始化位的无符号整数值；取其低min(Size, 64)个二进制位为初值，超出部分忽略。 |

## 返回值说明

无返回值。

## 约束说明

- 所属bitset的位数Size在编译期固定，操作不进行动态分配。默认构造所有位为0；整数构造读取输入低位并清除超出Size的位。

- 对于Size为0的空位图，整数构造忽略输入的全部位；count()为0，none()和all()都为true，to_ulong()和to_ullong()都返回0。这允许空分块复用相同的打包字导入/导出流程。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/bitset>

bool example()
{
    asc::std::bitset<8> bits(5);
    asc::std::bitset<0> empty(~0ULL);
    return bits.size() == 8 && bits.count() == 2 && empty.none() && empty.to_ullong() == 0;
}
```

## 关联API

- [本头文件的接口列表](asc_std_bitset.md)
