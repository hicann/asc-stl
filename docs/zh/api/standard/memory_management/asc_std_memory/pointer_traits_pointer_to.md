# asc::std::pointer_traits::pointer_to

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

`asc::std::pointer_traits::pointer_to`从对象引用构造与当前指针特征相容的指针。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 函数原型

所属类型：[`asc::std::pointer_traits`](pointer_traits.md)。以下声明摘要仅展示`element_type`不是`void`时可调用的形式，省略不可调用的占位参数类型。

```cpp
// pointer_traits<P>的类内声明摘要。
static constexpr pointer pointer_to(element_type& value);
```

```cpp
// pointer_traits<T*>的类内声明摘要。
static constexpr pointer pointer_to(element_type& value) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待以其地址构造pointer的对象引用；返回指针指向该对象。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `pointer` | 返回指向给定对象的对应指针类型。 |

## 约束说明

- 支持原始指针和用户自定义fancy pointer，接口自身不分配内存，返回指针的有效期受被引用对象的生命周期限制。
- C++17和C++20中包装函数均可用于常量求值；自定义指针的`pointer_to`、构造及返回类型也须满足相应的常量表达式要求。
- 自定义指针形式委托给该指针类型的静态`pointer_to`，其异常行为由具体实现决定；原始指针特化为`noexcept`。

## 调用示例

以下Host示例通过公开特征调用自定义指针，并在C++17和C++20中检查常量表达式结果。

```cpp
#include <asc/std/memory>

template<class T>
struct example_pointer {
    using element_type = T;
    T* value;
    static constexpr example_pointer pointer_to(T& object) noexcept { return {&object}; }
};

constexpr bool example()
{
    int object = 7;
    const auto pointer = asc::std::pointer_traits<example_pointer<int>>::pointer_to(object);
    return pointer.value == &object;
}

static_assert(example());
```

完整示例源码：[pointer_alignment.cpp](../../../../../../examples/standard/pointer_alignment/main.cpp)。

## 关联API

- [`asc::std::pointer_traits`](pointer_traits.md)
- [本头文件的接口列表](asc_std_memory.md)
