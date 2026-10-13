# asc::std::declval

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

`asc::std::declval`仅在未求值语境中形成指定类型的引用表达式。

标准语义参考：[cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility)。

## 函数原型

```cpp
namespace asc::std {
template<class T> asc::std::add_rvalue_reference_t<T> declval() noexcept;
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 在未求值上下文中取得假想引用表达式的类型；不要求可构造。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::std::add_rvalue_reference_t<T>` | 仅在未求值语境中形成指定类型的引用表达式。 |

## 约束说明

- 遵循标准约束。
- forward_like保留const/volatile限定和值类别。

## 调用示例

以下片段用具体类型展示调用；declval仅用于不求值的类型表达式。

```cpp
#include <asc/std/utility>

decltype(auto) example()
{
    using result = decltype(asc::std::declval<int>());
    return sizeof(result);
}
```

## 关联API

- [本头文件的接口列表](asc_std_utility.md)
