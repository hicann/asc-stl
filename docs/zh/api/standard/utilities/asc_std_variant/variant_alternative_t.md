# asc::std::variant_alternative_t

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

`asc::std::variant_alternative_t`取得给定索引处元素或备选项的类型。

标准语义参考：[cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant)。

## 声明

```cpp
namespace asc::std {
template<::std::size_t Index, class T> using variant_alternative_t = typename variant_alternative<Index, T>::type;
} // namespace asc::std
```

## 约束说明

- Device侧备选类型以及所选构造、赋值和交换操作必须不抛出异常。

## 调用示例

以下Host示例用具体类型和独立预期检查别名或标记结果。

```cpp
#include <asc/std/variant>
#include <asc/std/type_traits>

void use_type()
{
    using selected = asc::std::variant_alternative_t<0, asc::std::variant<int, float>>;
    static_assert(asc::std::is_same_v<selected, int>);
}
```

## 关联API

- [本头文件的接口列表](asc_std_variant.md)
