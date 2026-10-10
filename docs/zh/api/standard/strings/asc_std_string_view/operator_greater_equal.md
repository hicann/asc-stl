# asc::std::operator>=（函数）

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

头文件路径为：`<asc/std/string_view>`、`<asc/std/tuple>`、`<asc/std/utility>`。

按字符序列字典序判断左侧 string_view 是否不小于右侧。

标准语义参考：[cppreference `string_view`](https://en.cppreference.com/w/cpp/header/string_view)。

## 函数原型

### 原型 1

```cpp
[[nodiscard]] constexpr bool asc::std::operator>=(basic_string_view<CharT, Traits> left, basic_string_view<CharT, Traits> right) noexcept;
```

此原型对应头文件：`<asc/std/string_view>`。

### 原型 2

```cpp
[[nodiscard]] constexpr bool asc::std::operator>=(const tuple<>& left, const tuple<>& right) noexcept;
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型 3

```cpp
template<class T1, class T2> constexpr bool asc::std::operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) noexcept(noexcept(lhs < rhs));
```

此原型对应头文件：`<asc/std/utility>`。

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与本次比较或运算的左侧操作数。 |
| `right` | 输入 | 参与本次比较或运算的右侧操作数。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与本次比较或运算的左侧操作数。 |
| `right` | 输入 | 参与本次比较或运算的右侧操作数。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `T2` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `lhs` | 输入 | 提供按位置访问或组合的元素集合。 |
| `rhs` | 输入 | 提供按位置访问或组合的元素集合。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 2 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 3 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |

## 约束说明

- 提供构造、迭代和除 at 外的访问接口，以及 remove_prefix、remove_suffix、swap、data、size、starts_with、ends_with 和非抛出的比较/查找接口
- AI Core SIMD 编程 仅支持 local 或 generic 地址空间的普通字符指针
- 构造、赋值、交换及相关自由函数均不进行动态内存分配
- pair 操作不抛出异常
- 关系运算符均为显式提供

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/string_view>

decltype(auto) example(asc::std::string_view left, asc::std::string_view right)
{
    return (left >= right);
}
```
