# asc::std::ranges::range_adaptor_closure

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

`asc::std::ranges::range_adaptor_closure<Derived>`是自定义范围适配闭包的CRTP基类，使可调用对象参与范围管道及闭包组合。它不表示悬垂结果。

## 声明

公开CRTP基类只有一个模板参数Derived；用于把自定义可调用对象声明为范围适配闭包。

```cpp
namespace asc::std::ranges {
template<class Derived>
class range_adaptor_closure;
}
```

## 约束说明

- Derived须为不带cv限定的类类型，并以自身类型公开派生自本基类；本基类在C++17和C++20均可使用。
- 只有相应闭包调用表达式有效时，范围与闭包的管道以及闭包之间的组合才参与重载。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/ranges>
#include <asc/std/utility>

struct first_two : asc::std::ranges::range_adaptor_closure<first_two> {
    template<class R>
    auto operator()(R&& range) const
    {
        return asc::std::ranges::views::take(asc::std::forward<R>(range), 2);
    }
};

bool example()
{
    int values[3] = {1, 2, 3};
    auto result = values | first_two{};
    return result.size() == 2 && *result.begin() == 1;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
