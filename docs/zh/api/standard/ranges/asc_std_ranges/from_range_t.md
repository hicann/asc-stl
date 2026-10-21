# asc::std::from_range_t

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

`asc::std::from_range_t`是标识“从范围构造”重载的空标签类型；对应常量是`asc::std::from_range`。它不表示悬垂结果，也不保存或取得范围所有权。

## 声明

```cpp
namespace asc::std {
struct from_range_t;
} // namespace asc::std
```

## 约束说明

- 仅作为构造函数或函数重载的标签；具体类型是否有接收此标签的构造函数须查看该类型接口。
- 构造标签不开始遍历，不保存元素地址，也不延长范围的生命周期。

## 调用示例

`from_range_t`是区分范围构造重载的标记类型。以下检查公开标记对象的类型；容器是否支持该重载，以对应容器原型为准。

```cpp
#include <asc/std/ranges>
#include <asc/std/type_traits>

bool example()
{
    static_assert(asc::std::is_empty_v<asc::std::from_range_t>);
    static_assert(asc::std::is_same_v<decltype(asc::std::from_range), const asc::std::from_range_t>);
    return true;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
