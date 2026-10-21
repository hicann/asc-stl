# asc::std::variant_size

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

`asc::std::variant_size`取得variant的备选项数量。

标准语义参考：[cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant)。

## 声明

```cpp
namespace asc::std {
template<class T> struct variant_size;

template<class... Types>
struct variant_size<variant<Types...>> : integral_constant<size_t, sizeof...(Types)> {};

template<class T> struct variant_size<const T> : variant_size<T> {};
template<class T> struct variant_size<volatile T> : variant_size<T> {};
template<class T> struct variant_size<const volatile T> : variant_size<T> {};
}
```

## 约束说明

- 主模板作用于一个variant类型；const、volatile和const volatile形式是该主模板的偏特化，不是另一个可变参数主模板。

- Device侧备选类型以及所选构造、赋值和交换操作必须不抛出异常。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/variant>

bool example()
{
    static_assert(asc::std::variant_size<asc::std::variant<int, float>>::value == 2);
    return true;
}
```

## 关联API

- [本头文件的接口列表](asc_std_variant.md)
