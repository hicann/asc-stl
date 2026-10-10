# asc::std::operator&（函数模板）

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

`asc::std::operator&` 返回两个等长位集合的按位与结果。

标准语义参考：[cppreference `bitset`](https://en.cppreference.com/w/cpp/header/bitset)。

## 函数原型

```cpp
template<size_t Size> bitset<Size> asc::std::operator&(const bitset<Size>& lhs, const bitset<Size>& rhs) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Size` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `lhs` | 输入 | 提供“查询两个等长位集合的按位与结果”使用的对象引用；被引用对象须在调用期间有效。 |
| `rhs` | 输入 | 提供“查询两个等长位集合的按位与结果”使用的对象引用；被引用对象须在调用期间有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bitset<Size>` | 返回两个等长位集合的按位与结果。 |

## 约束说明

- 支持默认构造和 unsigned long long 构造
- operator[] 不进行边界检查
- 提供整组 set、reset、flip，位运算、移位、状态检查、计数和容量查询

## 调用示例

以下片段用具体类型展示调用；declval 仅用于不求值的类型表达式。

```cpp
#include <asc/std/bitset>

decltype(auto) example()
{
    asc::std::bitset<8> left(3u);
    asc::std::bitset<8> right(5u);
    return asc::std::operator&(left, right);
}
```
