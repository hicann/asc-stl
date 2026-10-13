# `asc::std::operator!=`（scoped_allocator）

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

头文件路径为：`<asc/std/scoped_allocator>`。

相等要求外层分配器及所有对应内层分配器相等；不等为相等结果的否定。

## 函数原型

以下为`asc::std`命名空间中的函数模板声明；执行空间宏已省略。

```cpp
template<class LeftOuter, class RightOuter, class... Inner>
constexpr bool operator!=(const scoped_allocator_adaptor<LeftOuter, Inner...>& left,
                          const scoped_allocator_adaptor<RightOuter, Inner...>& right) noexcept;
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 比较的左操作数，比较不修改它。 |
| `right` | 输入 | 比较的右操作数，比较不修改它。 |

`LeftOuter`、`RightOuter`分别是两侧外层分配器类型，`Inner...`是双方相同的内层分配器类型列表。

## 返回值说明

返回`bool`，比较关系成立时为`true`，否则为`false`。

## 约束说明

- 对应分配器须能进行相等比较。空的`Inner...`只比较外层分配器。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <memory>
#include <asc/std/scoped_allocator>

template<class T>
struct ExampleAllocator : ::std::allocator<T> {
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template<class U> struct rebind { using other = ExampleAllocator<U>; };
    ExampleAllocator() = default;
    template<class U> ExampleAllocator(const ExampleAllocator<U>&) noexcept {}
};

bool example()
{
    asc::std::scoped_allocator_adaptor<ExampleAllocator<int>> left, right;
    return !(left != right);
}
```

## 关联API

- [本头文件的接口列表](asc_std_scoped_allocator.md)
