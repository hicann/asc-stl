# asc::std::visit

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

头文件路径为：`<asc/std/variant>`。

`asc::std::visit` 以活动备选项调用访问器并返回结果。

标准语义参考：[cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant)。

## 函数原型

### 原型 1

```cpp
template<class Visitor, class Variant> constexpr decltype(auto) asc::std::visit(Visitor&& visitor, Variant&& value);
```

### 原型 2

```cpp
template<class Visitor, class Left, class Right> constexpr decltype(auto) asc::std::visit(Visitor&& visitor, Left&& left, Right&& right);
```

### 原型 3

```cpp
template<class Visitor, class First, class Second, class... Rest, enable_if_t<sizeof...(Rest) >= 1, int> = 0> constexpr auto asc::std::visit(Visitor&& visitor, First&& first, Second&& second, Rest&&... rest) -> decltype(asc::std::__visit_common_step<remove_cvref_t<Visitor>, remove_cvref_t<First>&, remove_cvref_t<Second>&, remove_cvref_t<Rest>&...>(asc::std::__make_indices_imp<variant_size_v<remove_cvref_t<First>>, 0>{}));
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Visitor` | 访问器可调用体类型。 |
| `Variant` | 被访问的 variant 类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `visitor` | 输入 | 以当前活动备选项调用的访问器。 |
| `value` | 输入 | 被访问的 variant。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Visitor` | 访问器可调用体类型。 |
| `Left`、`Right` | 两个被访问的 variant 类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `visitor` | 输入 | 以两个 variant 的活动备选项组合调用的访问器。 |
| `left`、`right` | 输入 | 被访问的两个 variant。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Visitor` | 访问器可调用体类型。 |
| `First`、`Second`、`Rest...` | 三个及以上被访问的 variant 类型。 |
| `未命名约束参数6` | 编译期约束参数（`sizeof...(Rest) >= 1`），调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `visitor` | 输入 | 以各 variant 活动备选项组合调用的访问器。 |
| `first`、`second`、`rest...` | 输入 | 被访问的三个及以上 variant。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1、2 | `decltype(auto)` | 访问器以活动备选项（组合）调用的结果，保持其值类别与类型。 |
| 原型 3 | 尾置推导类型 | 各备选类型组合调用结果的公共类型。 |

## 约束说明

- Device 侧备选类型以及所选构造、赋值和交换操作必须不抛出异常
- index、operator*、emplace、swap 和 visit 仅提供非抛出路径

## 调用示例

以下 Host 片段使用具体对象展示接口调用。

```cpp
#include <asc/std/variant>

decltype(auto) example()
{
    asc::std::variant<int, float> value{7};
    return asc::std::visit([](auto item) { return static_cast<int>(item); }, value);
}
```
