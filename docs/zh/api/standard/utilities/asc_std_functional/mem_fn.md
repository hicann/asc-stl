# asc::std::mem_fn

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

头文件路径为：`<asc/std/functional>`。

`asc::std::mem_fn`把成员指针包装为可调用对象。

标准语义参考：[cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional)。

## 函数原型

以下是调用形态摘要；返回可调用成员指针包装器，具体实现类型由头文件决定。

```cpp
namespace asc::std {
template<class R, class T>
constexpr auto mem_fn(R T::*member) noexcept;
}
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `R` | 成员指针的成员类型；函数成员时包含其函数类型。 |
| `T` | 成员指针所属的类类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `member` | 输入 | 成员对象或成员函数指针；返回的函数对象在调用时以给定对象、对象指针或reference_wrapper访问该成员。 |

## 返回值说明

返回可调用对象，具体实现类型由头文件决定。对象保存成员指针，调用时按invoke规则对提供的对象及参数执行成员访问或调用。

## 约束说明

- 支持标准可调用对象和成员指针形式。

## 调用示例

以下Host示例用具体输入和可判断结果展示本接口。

```cpp
#include <asc/std/functional>

struct widget { int read() const { return 3; } };

bool example()
{
    widget value;
    auto call = asc::std::mem_fn(&widget::read);
    return call(value) == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_functional.md)
