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
template<class T, size_t Size> struct array;
template<class T> struct array<T, 0>;
} // namespace asc::std
```

## 约束说明

- `Size`是编译期元素数量，可以为0。`Size == 0`时没有可访问的元素，不能调用下标、`front`、`back`或`get`访问元素。
- `Size > 0`时，`T`须能作为内建数组的元素类型；填充、比较和交换等操作还要求`T`支持相应的元素操作。
- 元素存储位于`array`对象内部，不由容器动态分配；元素类型自身的资源操作仍由`T`决定。
- 异常规格以各操作的声明为准。例如，非空数组的`fill`未声明`noexcept`，成员`swap`的`noexcept`取决于元素是否可无异常交换。Device侧使用的元素操作须不抛出异常。

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
