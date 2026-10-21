# asc::std::chrono::treat_as_floating_point

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

`asc::std::chrono::treat_as_floating_point`判断`Rep`是否按浮点计数处理，默认继承`is_floating_point`；自定义计数类型可在首次使用前显式特化。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 声明

```cpp
namespace asc::std::chrono {
template<class Rep> struct treat_as_floating_point;
} // namespace asc::std::chrono
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rep` | 待分类的时长计数类型；可为自定义类型。 |

## 约束说明

- 提供值运算以及六个显式关系运算符。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/chrono>

bool example()
{
    static_assert(asc::std::chrono::treat_as_floating_point<float>::value);
    static_assert(!asc::std::chrono::treat_as_floating_point<int>::value);
    return true;
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
