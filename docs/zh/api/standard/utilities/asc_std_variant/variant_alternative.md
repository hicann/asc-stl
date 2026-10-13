# asc::std::variant_alternative

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

头文件路径为：`<asc/std/variant>`。

`asc::std::variant_alternative`取得variant指定索引处备选项的类型。

标准语义参考：[cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant)。

## 声明

### 原型1

```cpp
namespace asc::std {
template<::std::size_t Index, class T> class variant_alternative;
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<size_t Index, class ...Types> struct variant_alternative;
} // namespace asc::std
```

### 原型3

```cpp
namespace asc::std {
template<size_t Index, class T> struct variant_alternative;
} // namespace asc::std
```

## 约束说明

- Device侧备选类型以及所选构造、赋值和交换操作必须不抛出异常。
- index、`operator*`、emplace、swap和visit仅提供非抛出路径。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/variant>
#include <asc/std/type_traits>

bool example()
{
    using Variant = asc::std::variant<int, float>;
    static_assert(asc::std::is_same_v<asc::std::variant_alternative<1, Variant>::type, float>);
    return true;
}
```

## 关联API

- [本头文件的接口列表](asc_std_variant.md)
