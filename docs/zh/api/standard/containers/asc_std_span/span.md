# asc::std::span

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

头文件路径为：`<asc/std/span>`。

`asc::std::span`以非拥有方式观察一段连续元素。

标准语义参考：[cppreference `span`](https://en.cppreference.com/w/cpp/header/span)。

## 声明

```cpp
namespace asc::std {
template<class T, size_t Extent = dynamic_extent> class span;
} // namespace asc::std
```

## 约束说明

- C++17和C++20均支持指针或连续迭代器与数量、连续迭代器与有大小的哨兵、数组、其他兼容span，以及连续且有大小的range构造。
- 迭代器或range的元素引用须能转换到`T`对应的元素类型；构造可写span时不能去掉元素的`const`，也不能按数组方式将派生类元素转换成基类元素。
- 非借用range须为左值，或者span的元素类型为`const`。span不拥有数据，原始元素在整个访问期间须保持有效。
- 固定extent须与输入数量一致。数组和固定span的静态extent不匹配时不参与构造；动态数量和range数量由调用方保证正确。
- 与数量可转换的第二实参按数量处理；异型哨兵须支持与迭代器的双向距离运算。
- AI Core SIMD编程中，元素指针或range须可表示为标准普通指针；此接口不增加GM/UB地址空间指针转换。

## 关键特性说明

C++17和C++20均提供类模板实参推导。内建数组和`asc::std::array`推导固定extent，泛型连续range推导动态extent。迭代器加整数常量类计数时，计数对象的常量值可用于推导固定extent；普通运行时数量保持动态extent。这些库接口的可用性不要求启用C++26语言模式。

## 调用示例

以下Host示例展示泛型range构造与静态extent推导，并检查视图对原数组的访问。

```cpp
#include <asc/std/span>
#include <asc/std/type_traits>

struct contiguous_values {
    int* first;
    asc::std::size_t count;
    int* begin() const { return first; }
    int* end() const { return first + count; }
    int* data() const { return first; }
    asc::std::size_t size() const { return count; }
};

bool example()
{
    int values[4] = {1, 2, 3, 4};
    contiguous_values range{values, 4};
    asc::std::span view(range);
    asc::std::span fixed(values, asc::std::integral_constant<asc::std::size_t, 4>{});
    static_assert(decltype(fixed)::extent == 4);
    view[1] = 8;
    auto tail = view.subspan(2, 2);
    return fixed[1] == 8 && tail.size() == 2 && tail[0] == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_span.md)
