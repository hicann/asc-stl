# asc::std::move_if_noexcept

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

`asc::std::move_if_noexcept`在移动构造不抛异常或复制不可用时返回右值引用，否则返回常量左值引用，让调用方按异常保证选择移动或复制路径。返回引用只在原对象存活期间有效。

标准语义参考：[cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility)。

## 函数原型

```cpp
namespace asc::std {
template<class T> constexpr asc::std::conditional_t<asc::std::is_nothrow_move_constructible_v<T> || !asc::std::is_copy_constructible_v<T>, T&&, const T&> move_if_noexcept(T& value) noexcept;
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 对象类型；须可复制构造或可按noexcept移动构造。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按条件移动的对象；当T可noexcept移动或不可复制时返回其右值引用（随之移动则移动后处于有效但未指定状态），否则返回const左值引用以走复制路径。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::std::conditional_t<asc::std::is_nothrow_move_constructible_v<T> \|\| !asc::std::is_copy_constructible_v<T>, T&&, const T&>` | 返回右值引用，否则返回常量左值引用，让调用方按异常保证选择移动或复制路径。 |

## 约束说明

- T必须满足所选移动或复制构造路径的要求。
- 返回引用不延长原对象生命周期。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/utility>
#include <asc/std/type_traits>

bool example()
{
    int value = 3;
    auto&& reference = asc::std::move_if_noexcept(value);
    static_assert(asc::std::is_same_v<decltype(reference), int&&>);
    // 在value仍存活时检查引用；函数只返回布尔值。
    return &reference == &value && reference == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_utility.md)
