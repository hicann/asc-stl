# asc::std::ranges::view_interface::back

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

头文件路径为：`<asc/std/ranges>`。

`asc::std::ranges::view_interface::back`返回末元素的引用；对象必须非空。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

所属类型：[`view_interface`](ranges_view_interface.md)。以下是按参与条件列出的声明摘要；保留供调用使用的模板默认值，省略仅供SFINAE的实现选择参数。涉及私有返回类型时用auto摘要表示，不承诺可直接命名该类型。

### 原型1

```cpp
template<class Derived2 = Derived>
constexpr decltype(auto) back();
```

`Derived2`须有双向迭代器，且起止迭代器类型相同。

### 原型2

```cpp
template<class Derived2 = Derived>
constexpr decltype(auto) back() const;
```

`const Derived2`须有双向迭代器，且起止迭代器类型相同。

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Derived2` | 用于延迟检查成员的所属类型或种类，默认值见原型；一般调用无需显式指定。 |

无函数参数。

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Derived2` | 用于延迟检查成员的所属类型或种类，默认值见原型；一般调用无需显式指定。 |

无函数参数。

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `decltype(auto)` | 返回末元素的引用或其迭代器解引用结果，保留该表达式的值类别。 |
| 原型2 | `decltype(auto)` | 返回末元素的引用或其迭代器解引用结果，保留该表达式的值类别。 |

## 约束说明

- 每种形式的参与条件见原型；无实参查询一般直接调用，不需要指定模板选择类型。
- 范围须非空，且相应迭代器可解引用。
- 返回的迭代器、指针或引用以及借用范围不得超过其实际依赖的视图对象和元素存储的有效期。

## 调用示例

以下Host片段在底层存储存活期内完成访问，返回元素值的副本，不把局部数组元素引用传出函数。

```cpp
#include <asc/std/ranges>

int read_last_element()
{
    int values[4] = {1, 2, 3, 4};
    asc::std::ranges::ref_view<int[4]> view(values);
    // 前置条件：视图非空（back 对空视图是未定义行为）
    return view.back();
}

bool verify_example()
{
    return read_last_element() == 4;
}
```

## 关联API

- [`asc::std::ranges::view_interface`](ranges_view_interface.md)
- [本头文件的接口列表](asc_std_ranges.md)
