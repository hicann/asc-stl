# asc::std::ranges::views::filter

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

`asc::std::ranges::views::filter` 只呈现满足谓词的元素。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 声明

该名称是公开的常量函数对象；对象的实现类型不构成接口承诺。以下为调用形式，省略的可选参数以各原型约束为准。

```cpp
asc::std::ranges::views::filter(range, predicate)
```

```cpp
asc::std::ranges::views::filter(predicate)
```

## 参数说明

### 调用形式 1 的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `range` | 输入 | 待访问或变换的输入范围；借用结果受其生命周期约束。 |
| `predicate` | 输入 | 对元素或投影结果执行判断的谓词。 |

### 调用形式 2 的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `predicate` | 输入 | 对元素或投影结果执行判断的谓词。 |

## 返回值说明

传入范围和配置时返回惰性视图；仅传配置时返回可与范围组合的视图适配器。

| 调用形式 | 返回类型 |
| --- | --- |
| 范围与谓词 | `filter_view<decltype(views::all(range)), Predicate>` |
| 仅传配置参数 | 可与范围组合的适配器闭包类型；具体实现类型不构成接口承诺 |

## 约束说明

- C++20 视图不进行动态内存分配
- owning_view 仅拥有调用方传入的范围对象，不产生额外分配

## 调用示例

以下 Host 片段以具体数组或数值演示本页调用形式。

```cpp
#include <asc/std/ranges>

void example()
{
    // 用具体类型和实参演示已交付的调用形式。
    int values[4] = {1, 2, 3, 4};
    auto predicate = [](int value) { return value % 2 == 0; };
    auto result_1 = asc::std::ranges::views::filter(values, predicate);
    (void)result_1;
    auto result_2 = asc::std::ranges::views::filter(predicate)(values);
    (void)result_2;
}
```
