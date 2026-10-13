# asc::std::as_const

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

`asc::std::as_const`以常量左值引用观察已有对象而不复制它。

标准语义参考：[cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility)。

## 函数原型

```cpp
namespace asc::std {
template<typename T> [[nodiscard]] constexpr add_const_t<T>& as_const(T& value) noexcept;
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 被观察对象的类型（不能是const限定的对象类型）。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 被以常量视角观察的对象；返回其const左值引用，对象本身不被修改也不被复制。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `add_const_t<T> &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |

## 约束说明

- 遵循标准约束。
- forward_like保留const/volatile限定和值类别。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/utility>
#include <asc/std/type_traits>

bool example()
{
    int value = 3;
    auto&& reference = asc::std::as_const(value);
    static_assert(asc::std::is_same_v<decltype(reference), const int&>);
    // 在value仍存活时检查引用；函数只返回布尔值。
    return &reference == &value && reference == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_utility.md)
