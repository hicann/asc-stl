# asc::std::void_t

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

`void_t<Types...>`在所列类型均有效时产生`void`，用于C++17检测式约束。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

```cpp
namespace asc::std {
template<class... Types>
using void_t = void;
}
```

## 约束说明

- 每个模板实参必须是有效类型；替换成功时结果恒为`void`，可用于检测依赖类型或表达式是否有效。

## 调用示例

以下Host片段用`static_assert`验证特征结果，并以检测惯用法演示`void_t`的典型用途。

```cpp
#include <asc/std/type_traits>

template <class T, class = asc::std::void_t<>>
struct has_value_type : asc::std::false_type
{};

template <class T>
struct has_value_type<T, asc::std::void_t<typename T::value_type>> : asc::std::true_type
{};

void use_void_t()
{
    // void_t 的结果就是 void
    static_assert(asc::std::is_same_v<asc::std::void_t<int>, void>);

    // 检测惯用法：void_t 让“表达式合法”的实参走真分支，成员不存在时落入 false_type
    struct with_value_type
    {
        using value_type = int;
    };
    static_assert(has_value_type<with_value_type>::value);
    static_assert(!has_value_type<int>::value);
}
```

## 关联API

- [本头文件的接口列表](asc_std_type_traits.md)
