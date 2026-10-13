# asc::std::operator>（string_view 重载）（函数模板）

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

头文件路径为：`<asc/std/string_view>`。

按字符序列字典序判断左侧 string_view 是否大于右侧。

标准语义参考：[cppreference `string_view`](https://en.cppreference.com/w/cpp/header/string_view)。

## 函数原型

### 原型 1

```cpp
template<class CharT, class Traits> constexpr bool asc::std::operator>(basic_string_view<CharT, Traits> left, basic_string_view<CharT, Traits> right) noexcept;
```

此原型对应头文件：`<asc/std/string_view>`。

### 原型 2

```cpp
template<class C, class T, int = 1> constexpr bool asc::std::operator>(basic_string_view<C, T> left, type_identity_t<basic_string_view<C, T>> right) noexcept;
```

此原型对应头文件：`<asc/std/string_view>`。异构形式：右操作数可由可转换为 `basic_string_view<C, T>` 的类型（如字符串字面量）隐式构造。

### 原型 3

```cpp
template<class C, class T, unsigned int = 2> constexpr bool asc::std::operator>(type_identity_t<basic_string_view<C, T>> left, basic_string_view<C, T> right) noexcept;
```

此原型对应头文件：`<asc/std/string_view>`。异构形式：左操作数可由可隐式转换的源类型构造。

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `CharT` | basic_string_view 的字符类型；须满足原型中的类型约束。 |
| `Traits` | basic_string_view 的字符特性类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与比较的左侧 string_view。 |
| `right` | 输入 | 参与比较的右侧 string_view。 |

### 原型 2、3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `C`、`T` | 字符类型与字符特性类型。 |
| `未命名约束参数3` | 编译期消歧参数（区分两个异构方向的宏生成重载），调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left`、`right` | 输入 | 参与比较的两个 string_view（其中一侧可为可隐式转换的源类型，如字符串字面量）。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1-3 | `bool` | 按字典序比较成立时为 `true`，否则为 `false`。 |

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
    return (left > right);
}
```

tuple 比较运算符见 [tuple 重载页](../../utilities/asc_std_tuple/tuple_operator_greater.md)。
