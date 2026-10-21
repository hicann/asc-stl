# asc::std::iterator_traits

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

头文件路径为：`<asc/std/iterator>`。

`asc::std::iterator_traits`在编译期取得对应迭代器属性类型。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 声明

```cpp
namespace asc::std {
template<class Iter, class = void>
struct iterator_traits;
}
```

主模板允许省略第二个模板参数。对提供五个传统关联类型的迭代器，特征复制其嵌套类型；不满足选择条件时主模板可为空。对象指针具有以下偏特化：

```cpp
namespace asc::std {
template<class T>
struct iterator_traits<T*, enable_if_t<is_convertible_v<T(*)[], const volatile void*>>> {
    using difference_type = ptrdiff_t;
    using value_type = remove_cv_t<T>;
    using pointer = T*;
    using reference = T&;
    using iterator_category = random_access_iterator_tag;
    using iterator_concept = contiguous_iterator_tag;
};
}
```

## 约束说明

- 提供C++20公开迭代器概念和特征接口。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>
#include <asc/std/type_traits>

bool example()
{
    struct custom_iterator {
        using difference_type = short;
        using value_type = long;
        using pointer = long*;
        using reference = long&;
        using iterator_category = asc::std::input_iterator_tag;
    };
    using generic_traits = asc::std::iterator_traits<custom_iterator>;
    using pointer_traits = asc::std::iterator_traits<const int*>;
    static_assert(asc::std::is_same_v<generic_traits::difference_type, short>);
    static_assert(asc::std::is_same_v<generic_traits::iterator_category, asc::std::input_iterator_tag>);
    static_assert(asc::std::is_same_v<pointer_traits::value_type, int>);
    static_assert(asc::std::is_same_v<pointer_traits::iterator_concept, asc::std::contiguous_iterator_tag>);
    return true;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
