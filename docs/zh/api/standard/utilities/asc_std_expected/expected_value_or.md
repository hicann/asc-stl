# asc::std::expected::value_or

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

头文件路径为：`<asc/std/expected>`。

`asc::std::expected::value_or`在对象有值时返回该值，否则返回调用方提供的替代值。

标准语义参考：[cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected)。

## 函数原型

以下为`expected<Value, Error>`类内声明；Value和Error是所属类模板参数。

```cpp
constexpr Value value_or(const Value& fallback) const;
```

```cpp
template<class Up> constexpr Value value_or(Up&& fallback) const&;
```

```cpp
template<class Up> constexpr Value value_or(Up&& fallback) &&;
```

## 参数说明

**模板参数（模板重载）**

| 参数名 | 描述 |
| --- | --- |
| `Up` | 替代值的来源类型；须能转换为Value。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `fallback` | 输入/输出（转发形式） | 在相应状态下作为替代值使用；右值来源可被移动。 |

## 返回值说明

返回Value。有值时复制或移动成功值，否则把fallback转换为Value。

## 约束说明

- 所属expected<Value, Error>要求有效的非void值类型和错误对象类型；当前操作还须满足本页原型、参数和状态要求。对成功值或错误值的传播分别受相应cv/ref形式的可调用、可构造条件约束。

## 调用示例

以下Host片段使用具体类型演示调用；访问值前须确认对象处于有值状态。

```cpp
#include <asc/std/expected>

decltype(auto) example()
{
    asc::std::expected<int, int> value(7);
    return value.value_or(0);
}

bool verify_example()
{
    return example() == 7;
}
```

## 关联API

- [`asc::std::expected`](expected.md)
- [本头文件的接口列表](asc_std_expected.md)
