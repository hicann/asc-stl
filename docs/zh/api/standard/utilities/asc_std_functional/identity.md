# asc::std::identity

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

`asc::std::identity`原样返回调用实参的函数对象。

标准语义参考：[cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional)。

## 声明

```cpp
namespace asc::std {
struct identity;
} // namespace asc::std
```

## 约束说明

- 同时提供指定类型形式和透明调用形式。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/functional>

bool example()
{
    int value = 7;
    auto&& result = asc::std::identity{}(value);
    return &result == &value && result == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_functional.md)
