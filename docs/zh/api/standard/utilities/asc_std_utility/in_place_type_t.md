# asc::std::in_place_type_t

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

头文件路径为：`<asc/std/utility>`。

`asc::std::in_place_type_t`标记按备选项类型原位构造对象。

标准语义参考：[cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility)。

## 声明

```cpp
namespace asc::std {
template<class T> struct in_place_type_t;
} // namespace asc::std
```

## 约束说明

- 提供完整的标准形式。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/utility>
#include <asc/std/variant>

bool example()
{
    asc::std::variant<int, float> value(asc::std::in_place_type_t<int>{}, 7);
    return value.index() == 0 && *asc::std::get_if<int>(&value) == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_utility.md)
