# asc::std::ranges::operator|

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

`asc::std::ranges::operator|`由`<asc/std/ranges>`提供，两个区间适配器闭包的管道组合运算，产出等价依次施打的组合闭包。接口遵循对应C++ 标准设施的语义；ASC-STL的语言模式和调用位置以本页声明为准。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

```cpp
namespace asc::std::ranges {
template<class Closure, class OtherClosure> constexpr auto operator|(Closure&& closure, OtherClosure&& other_closure) noexcept(asc::std::is_nothrow_constructible_v<asc::std::decay_t<Closure>, Closure> && asc::std::is_nothrow_constructible_v<asc::std::decay_t<OtherClosure>, OtherClosure>);
} // namespace asc::std::ranges
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Closure` | 左侧区间适配器闭包的类型。 |
| `OtherClosure` | 右侧区间适配器闭包的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `OtherClosure` | 输入 | 参与操作的对象引用；调用期间被引用对象须保持有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `auto` | 将区间传入右侧闭包所得的视图，或将两个闭包组合后得到的新闭包。 |

## 约束说明

- 两侧实参须均为区间适配器闭包；组合结果仍为闭包，对区间施打等价于按序先左后右调用。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/ranges>
#include <asc/std/array>
#include <asc/std/iterator>
#include <asc/std/tuple>

bool example()
{
    int values[] = {1, 2, 3, 4};
    auto view = values | asc::std::ranges::views::drop(1) | asc::std::ranges::views::take(2);
    return *view.begin() == 2 && view.size() == 2;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
