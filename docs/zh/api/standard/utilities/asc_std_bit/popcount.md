# asc::std::popcount

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

头文件路径为：`<asc/std/bit>`。

`asc::std::popcount` 统计置位的二进制位数。

标准语义参考：[cppreference `bit`](https://en.cppreference.com/w/cpp/header/bit)。

## 函数原型

```cpp
template<class T> [[nodiscard]] constexpr int asc::std::popcount(T value) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `int` | 返回对应前导位、尾随位或全部置位位的数量。 |

## 约束说明

- 遵循标准无符号整数类型约束

## 调用示例

以下片段用具体数值展示本页调用。

```cpp
#include <asc/std/bit>

decltype(auto) example()
{
    return asc::std::popcount(7u);
}
```
