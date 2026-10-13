# asc::std::gcd

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

头文件路径为：`<asc/std/numeric>`。

`asc::std::gcd` 计算两个整数的最大公约数。

标准语义参考：[cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric)。

## 函数原型

```cpp
template<class T, class U> [[nodiscard]] constexpr common_type_t<T, U> asc::std::gcd(T left, U right);
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 左操作数的整数类型；不含 bool。 |
| `U` | 右操作数的整数类型；不含 bool。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 求最大公约数的左整数操作数。 |
| `right` | 输入 | 求最大公约数的右整数操作数。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `common_type_t<T, U>` | 返回两个整数的最大公约数的计算结果。 |

## 约束说明

- 模板参数 `T`、`U` 须为整型且非 `bool`，否则触发编译期断言
- 两参数的绝对值均须能由公共结果类型 `common_type_t<T, U>` 表示，否则结果无定义
## 调用示例

以下片段用具体整数范围展示数值调用；输出数组具有足够容量。

```cpp
#include <asc/std/numeric>

decltype(auto) example()
{
    return asc::std::gcd(12, 18);
}
```
