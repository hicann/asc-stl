# `asc::std::operator>=`（tuple）

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

头文件路径为：`<asc/std/tuple>`。

`asc::std::operator>=`（tuple自由比较函数模板） 判断左操作数是否不小于右操作数。

标准语义参考：[cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple)。

## 函数原型

```cpp
template<class... Left, class... Right> constexpr bool asc::std::operator>=(const tuple<Left...>& left, const tuple<Right...>& right);
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Left`、`Right` | 两个tuple的元素类型包，元素个数须相同。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left`、`right` | 输入 | 参与比较的两个tuple。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 两tuple按字典序大于等于比较时为`true`，否则为`false`。 |

## 约束说明

- 两侧tuple的元素数量必须相同；各对应元素须支持本运算要求的比较。
- 相等要求全部对应元素相等；顺序比较按字典序，从首个不等元素确定结果。

## 调用示例

以下Host片段使用具体数值类型演示调用；状态与参数须满足本页约束。

```cpp
#include <asc/std/tuple>

decltype(auto) example()
{
    asc::std::tuple<int, int> left(1, 2), right(3, 4);
    return (left >= right);
}
```

## 关联API

- [本头文件的接口列表](asc_std_tuple.md)
