# asc::std::forward_like

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

`asc::std::forward_like`按示范类型复制const/volatile限定和值类别。

标准语义参考：[cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility)。

## 函数原型

以下是调用形态摘要；返回引用的cv限定和值类别以T&&为模型应用到U，实际类型通过实现中的类型计算取得。

```cpp
namespace asc::std {
template<class T, class U>
[[nodiscard]] constexpr decltype(auto) forward_like(U&& value) noexcept;
}
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 提供目标const/volatile限定和左／右值引用类别的参考类型。 |
| `U` | 被转发实参的推导类型；返回表达式合并T指定的const/volatile限定并保持U的已有限定和引用类别。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 提供“按示范类型复制const/volatile限定和值类别”使用的对象引用；被引用对象须在调用期间有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `decltype(auto)` | 返回按示范类型保留限定和值类别的引用，不构造新对象。 |

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
    auto&& reference = asc::std::forward_like<int&>(value);
    static_assert(asc::std::is_same_v<decltype(reference), int&>);
    // 在value仍存活时检查引用；函数只返回布尔值。
    return &reference == &value && reference == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_utility.md)
