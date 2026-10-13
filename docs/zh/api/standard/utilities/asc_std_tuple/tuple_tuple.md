# asc::std::tuple::tuple

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

`asc::std::tuple::tuple`按本页所列构造形态初始化`tuple`对象。

标准语义参考：[cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple)。

## 函数原型

以下为`asc::std::tuple<Types...>`的类内构造声明；`Types...`来自所属类模板。

### 原型1

```cpp
constexpr tuple();
```

### 原型2

```cpp
tuple(const tuple<Types...>& other);
```

### 原型3

```cpp
tuple(tuple<Types...>&& other);
```

### 原型4

```cpp
template<class... Values, enable_if_t<sizeof...(Values) == sizeof...(Types), int> = 0> constexpr explicit tuple(Values&&... values);
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 构造来源对象；本对象由其对应成员或底层状态初始化，右值形式可移动该状态。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 构造来源对象；本对象由其对应成员或底层状态初始化，右值形式可移动该状态。 |

### 原型4的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Values` | 传递给构造函数或可调用对象的实参类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `values` | 输入/输出 | 逐元素构造的转发实参包；第i个实参经转发（左值复制、右值移动）初始化新tuple的第i个元素，被移动的右值实参随后处于有效但未指定状态。 |
## 返回值说明

无返回值。

## 约束说明

- 构造、赋值、交换及相关自由函数均不进行动态内存分配。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/tuple>
#include <asc/std/utility>

bool example()
{
    asc::std::tuple<int, int> zero;
    asc::std::tuple<int, int> values(2, 4);
    auto copy = values;
    auto moved = asc::std::move(copy);
    return asc::std::get<0>(zero) == 0 && asc::std::get<0>(moved) == 2 && asc::std::get<1>(moved) == 4;
}
```

## 关联API

- [本头文件的接口列表](asc_std_tuple.md)
