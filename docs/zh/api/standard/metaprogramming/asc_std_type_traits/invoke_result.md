# asc::std::invoke_result

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

`asc::std::invoke_result`取得以给定参数调用函数对象时的结果类型。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

```cpp
namespace asc::std {
template<class Fp, class ...Args> struct invoke_result;
} // namespace asc::std
```

## 约束说明

- 仅当按`asc::std::invoke`规则以`Args...`调用`Fn`的表达式有效时提供结果成员`type`，并保留该表达式的返回引用类别。

## 调用示例

以下Host片段用具体类型实参和`static_assert`验证本页类型特征的结果。

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    struct Functor { double operator()(int) const { return 0.5; } }; // 局部仿函数
    // 函数指针以 int 调用的结果类型
    static_assert(asc::std::is_same_v<asc::std::invoke_result<int (*)(int), int>::type, int>);
    static_assert(asc::std::is_same_v<asc::std::invoke_result_t<Functor, int>, double>);
    // 反例：Functor 以 int 调用不返回 int
    static_assert(!asc::std::is_same_v<asc::std::invoke_result_t<Functor, int>, int>);
}
```

## 关联API

- [本头文件的接口列表](asc_std_type_traits.md)
