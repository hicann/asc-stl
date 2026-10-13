# asc::std::array

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

头文件路径为：`<asc/std/array>`。

`asc::std::array`连续保存编译期固定数量的元素。

标准语义参考：[cppreference `array`](https://en.cppreference.com/w/cpp/header/array)。

## 声明

```cpp
namespace asc::std {
template<class T, size_t Size> class array;
} // namespace asc::std
```

## 约束说明

- 支持包括零在内的所有N。
- 成员函数和自由函数均不抛出异常。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/array>

bool example()
{
    asc::std::array<int, 3> values{{1, 2, 3}};
    values[1] = 7;
    return values.size() == 3 && values.front() == 1 && values[1] == 7 && values.back() == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_array.md)
