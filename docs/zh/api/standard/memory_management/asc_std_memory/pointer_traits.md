# asc::std::pointer_traits

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

头文件路径为：`<asc/std/memory>`。

`asc::std::pointer_traits`统一访问指针类对象的元素类型与地址操作。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 声明

第一行是主模板，第二行是原始指针偏特化；第二模板参数是默认选择参数，调用通常只写pointer_traits<Ptr>。

```cpp
namespace asc::std {
template<class Ptr, class = void> struct pointer_traits;
template<class T> struct pointer_traits<T*>;
}
```

## 约束说明

- 原始指针`T*`直接提供`pointer=T*`、`element_type=T`、`difference_type=ptrdiff_t`以及`rebind<U>=U*`。
- 泛型指针优先使用其`element_type`；若没有，则可从`SomePointer<T, Args...>`形式的首个类型实参推导。无法得到元素类型时不提供这些成员。
- 泛型`difference_type`优先使用指针类型自带成员，否则为`ptrdiff_t`；`rebind`优先使用指针的同名别名，否则替换上述模板形式的首个类型实参。
- 不分配存储；`pointer_to`返回指针的有效期受原对象生命周期限制。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/memory>

bool example()
{
    int value = 7;
    int* pointer = asc::std::pointer_traits<int*>::pointer_to(value);
    return pointer == &value && *pointer == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_memory.md)
