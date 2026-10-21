# asc::std::exchange

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

`asc::std::exchange`以新值替换对象并返回旧值。

标准语义参考：[cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility)。

## 函数原型

```cpp
namespace asc::std {
template<class T, class U = T>
constexpr T exchange(T& object, U&& new_value)
    noexcept(is_nothrow_move_constructible_v<T> && is_nothrow_assignable_v<T&, U>);
}
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 被替换对象的类型；须可移动构造且可被T2赋值。 |
| `T2` | 新值的类型；须可赋给T1&。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `object` | 输入/输出 | 被替换的对象；其旧值经移动作为返回值返回，调用后保存new_value。 |
| `new_value` | 输入/输出 | 赋给object的新值；以右值赋值时被移动，移动后处于有效但未指定状态。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T1` | 返回旧值。 |

## 约束说明

- 遵循标准约束。
- forward_like保留const/volatile限定和值类别。

## 调用示例

以下片段用具体数值展示本页调用。

```cpp
#include <asc/std/utility>

decltype(auto) example()
{
    int value = 3;
    return asc::std::exchange(value, 4);
}
```

## 关联API

- [本头文件的接口列表](asc_std_utility.md)
