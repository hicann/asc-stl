# asc::std::iterator_traits::iterator_category

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

`asc::std::iterator_traits::iterator_category`标识迭代器的传统类别标签。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 声明

传统五成员特征分支从`Iter::iterator_category`取得类型；若所选特征分支不提供它，该成员不存在。

以下别名仅属于[`iterator_traits<T*>`](iterator_traits.md)的对象指针偏特化，不能推广到所有迭代器：

```cpp
// iterator_traits<T*> 的对象指针偏特化类内节选。
using iterator_category = random_access_iterator_tag;
```

## 约束说明

- 成员是否存在及其类型由所选特征分支决定；自定义迭代器应提供匹配的关联类型。

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
    using selected = typename asc::std::iterator_traits<custom_iterator>::iterator_category;
    static_assert(asc::std::is_same_v<selected, asc::std::input_iterator_tag>);
    return true;
}
```

## 关联API

- [`asc::std::iterator_traits`](iterator_traits.md)
- [本头文件的接口列表](asc_std_iterator.md)
