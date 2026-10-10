# asc::std::bitset::operator[]

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

`asc::std::bitset::operator[]` 在调用方保证索引有效时访问指定元素。

标准语义参考：[cppreference `bitset`](https://en.cppreference.com/w/cpp/header/bitset)。

## 函数原型

### 原型 1

```cpp
const_reference asc::std::bitset::operator[](size_t position) const;
```

### 原型 2

```cpp
reference asc::std::bitset::operator[](size_t position);
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `position` | 输入 | 要访问的元素索引；调用方须保证索引在有效范围内。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `position` | 输入 | 要访问的元素索引；调用方须保证索引在有效范围内。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `const_reference` | 返回指定索引处的元素引用或代理值；索引必须有效。 |
| 原型 2 | `reference` | 返回指定索引处的元素引用或代理值；索引必须有效。 |

## 约束说明

- 支持默认构造和 unsigned long long 构造
- operator[] 不进行边界检查
- 提供整组 set、reset、flip，位运算、移位、状态检查、计数和容量查询

## 调用示例

以下 Host 片段以 8 位 bitset 演示具体调用；索引须在有效范围内。

```cpp
#include <asc/std/bitset>

decltype(auto) example(const asc::std::bitset<8>& bits)
{
    return bits[0];
}
```
