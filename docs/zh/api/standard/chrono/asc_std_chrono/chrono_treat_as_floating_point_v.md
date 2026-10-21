# asc::std::chrono::treat_as_floating_point_v

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

头文件路径为：`<asc/std/chrono>`。

`asc::std::chrono::treat_as_floating_point_v`表示给定时长表示类型是否按浮点数处理。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 声明

位于asc::std::chrono命名空间；变量模板读取trait值，包含对用户自定义Rep的显式特化。

```cpp
template<class Rep>
inline constexpr bool treat_as_floating_point_v = treat_as_floating_point<Rep>::value;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rep` | 读取对应treat_as_floating_point特化的计数类型。 |

## 约束说明

- Rep是时长的计数表示类型；默认依据is_floating_point判断。
- 自定义计数类型可在首次使用前显式特化treat_as_floating_point；_v读取该特化的value。
- duration构造使用该值决定是否允许从浮点计数初始化；其它可转换性及可表示性要求仍须满足。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/chrono>
#include <asc/std/type_traits>

struct custom_rep {
    float value;
    constexpr custom_rep(float input) : value(input) {}
};

namespace asc::std::chrono {
template <> struct treat_as_floating_point<custom_rep> : true_type {};
}

static_assert(!asc::std::is_floating_point_v<custom_rep>);
static_assert(asc::std::chrono::treat_as_floating_point_v<custom_rep>);

bool example()
{
    const asc::std::chrono::duration<custom_rep> value(1.5F);
    return value.count().value == 1.5F;
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
