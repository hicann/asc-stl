# asc::std::ranges::cdata

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

`asc::std::ranges::cdata` 从左值连续范围取得只读首元素地址；返回指针不拥有底层存储。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 声明

该名称是公开的常量函数对象；对象的实现类型不构成接口承诺。以下为调用形式，省略的可选参数以各原型约束为准。

```cpp
asc::std::ranges::cdata(range)
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `range` | 输入 | 待访问或变换的输入范围；借用结果受其生命周期约束。 |

## 返回值说明

返回指向连续范围首元素的指针；有效期受输入范围约束。

| 调用形式 | 返回类型 |
| --- | --- |
| 左值范围 | `decltype(ranges::data(static_cast<const T&>(range)))` |

## 约束说明

- 支持数组和用户范围，不支持仅由花括号构成的 initializer_list 表达式
- 当前实现仅接受左值范围
- 调用方须使底层范围在结果使用期间保持有效。

## 调用示例

以下 Host 片段以具体数组或数值演示本页调用形式。

```cpp
#include <asc/std/ranges>

void example()
{
    // 用具体类型和实参演示已交付的调用形式。
    int values[4] = {1, 2, 3, 4};
    auto result_1 = asc::std::ranges::cdata(values);
    (void)result_1;
}
```
