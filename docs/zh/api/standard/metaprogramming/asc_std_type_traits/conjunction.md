# asc::std::conjunction

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

`asc::std::conjunction`对一组布尔特征执行短路逻辑与。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

```cpp
namespace asc::std {
template <class... Args>
struct conjunction;
}  // namespace asc::std
```

## 约束说明

- 求值到的实参须提供可转换为`bool`的`value`。继承第一个为false的实参，全部为true时继承最后一个实参；空参数包为true，后续实参按短路规则处理。

## 调用示例

以下Host片段用具体类型实参和`static_assert`验证本页类型特征的结果。

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    // 全部谓词为真时整体为真
    static_assert(asc::std::conjunction<asc::std::true_type, asc::std::is_integral<int>>::value);
    static_assert(asc::std::conjunction_v<asc::std::is_integral<int>, asc::std::true_type>);
    // 反例：任一谓词为假则整体为假
    static_assert(!asc::std::conjunction_v<asc::std::true_type, asc::std::is_integral<double>>);
    struct no_value {};
    // 首个实参已为false，不实例化后续实参的value。
    static_assert(!asc::std::conjunction_v<asc::std::false_type, no_value>);
}
```

## 关联API

- [本头文件的接口列表](asc_std_type_traits.md)
