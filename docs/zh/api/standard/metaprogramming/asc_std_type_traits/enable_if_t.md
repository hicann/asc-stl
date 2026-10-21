# asc::std::enable_if_t

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

头文件路径为：`<asc/std/type_traits>`。

`asc::std::enable_if_t`仅在编译期条件成立时提供成员类型以参与重载选择，以类型别名形式提供结果。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

```cpp
namespace asc::std {
template<bool Value, class T = void>
using enable_if_t = typename enable_if<Value, T>::type;
} // namespace asc::std
```

## 约束说明

- 本辅助形式与[`asc::std::enable_if`](enable_if.md)使用相同的类型前提和判定规则；结果对应特征类的`type`。

## 调用示例

以下Host示例使用独立的预期类型或值检查接口结果。

```cpp
#include <asc/std/type_traits>

using result_type = asc::std::enable_if_t<true, int>;
static_assert(asc::std::is_same_v<result_type, int>);
```

## 关联API

- [本头文件的接口列表](asc_std_type_traits.md)
