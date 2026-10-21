# asc::std::conjunction_v

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

`asc::std::conjunction_v`对一组布尔特征执行短路逻辑与，以bool变量模板形式提供结果。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

以下声明摘要用公开特征类的`value`表示等价的常量值。

```cpp
namespace asc::std {
template<class ...Args>
inline constexpr bool conjunction_v = conjunction<Args...>::value;
} // namespace asc::std
```

## 约束说明

- 本辅助形式与[`asc::std::conjunction`](conjunction.md)使用相同的类型前提和判定规则；结果对应特征类的`value`。

## 调用示例

以下Host片段用具体类型实参实例化本页类型特征。

```cpp
#include <asc/std/type_traits>

static_assert((asc::std::conjunction_v<asc::std::true_type, asc::std::false_type>) == false);
```

## 关联API

- [本头文件的接口列表](asc_std_type_traits.md)
