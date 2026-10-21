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

`asc::std::visit`以活动备选项调用访问器并返回结果。

标准语义参考：[cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant)。

## 函数原型

以下为公开**调用形态摘要**；三参数以上的推导结果由各活动项组合调用结果的公共类型计算得到，省略其实现辅助类型。

```cpp
namespace asc::std {
template<class Visitor, class Variant>
constexpr decltype(auto) visit(Visitor&& visitor, Variant&& value);
}
```

```cpp
namespace asc::std {
template<class Visitor, class Left, class Right>
constexpr decltype(auto) visit(Visitor&& visitor, Left&& left, Right&& right);
}
```

```cpp
namespace asc::std {
template<class Visitor, class First, class Second, class... Rest, enable_if_t<(sizeof...(Rest) >= 1), int> = 0>
constexpr auto visit(Visitor&& visitor, First&& first, Second&& second, Rest&&... rest);
}
```

```cpp
namespace asc::std {
template<class Result, class Visitor, class... Variants>
constexpr Result visit(Visitor&& visitor, Variants&&... variants);
}
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Visitor` | 访问器可调用体类型。 |
| `Variant` | 被访问的variant类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `visitor` | 输入 | 以当前活动备选项调用的访问器。 |
| `value` | 输入 | 被访问的variant。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Visitor` | 访问器可调用体类型。 |
| `Left`、`Right` | 两个被访问的variant类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `visitor` | 输入 | 以两个variant的活动备选项组合调用的访问器。 |
| `left`、`right` | 输入 | 被访问的两个variant。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Visitor` | 访问器可调用体类型。 |
| `First`、`Second`、`Rest...` | 三个及以上被访问的variant类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `visitor` | 输入 | 以各variant活动备选项组合调用的访问器。 |
| `first`、`second`、`rest...` | 输入 | 被访问的三个及以上variant。 |

## 返回值说明

默认入口对所有可能活动项组合的调用结果求公共类型，并把实际结果转换为该类型；即使声明使用decltype(auto)，也不保证保留访问器返回的引用或值类别。显式Result入口将默认visit结果再转换为Result，要求该转换有效。

## 约束说明

- 调用前所有被访问的`variant`都须有活动备选项；先检查`valueless_by_exception()`，不得访问无活动项的对象。

- 至少提供一个variant，访问前所有输入都须持有有效活动项。访问器对所需备选项组合须可调用且结果具备公共类型；显式Result形式仍依赖默认入口的结果计算。

- Device侧备选类型以及所选构造、赋值和交换操作必须不抛出异常。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/variant>
#include <asc/std/type_traits>

struct value_reference {
    int& operator()(int& value) const { return value; }
};

bool example()
{
    asc::std::variant<int> value(7);
    static_assert(asc::std::is_same_v<decltype(asc::std::visit(value_reference{}, value)), int>);
    const auto result = asc::std::visit(value_reference{}, value);
    const long converted = asc::std::visit<long>(value_reference{}, value);
    return result == 7 && converted == 7L;
}
```

## 关联API

- [本头文件的接口列表](asc_std_variant.md)
