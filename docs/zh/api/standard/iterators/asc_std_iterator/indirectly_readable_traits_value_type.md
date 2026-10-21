# asc::std::indirectly_readable_traits::value_type

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

`asc::std::indirectly_readable_traits::value_type`标识元素或结果的值类型。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 声明

`value_type`只在可确定可读取对象类型时出现。实际选择规则如下：

| 输入类型 | `value_type` |
| --- | --- |
| 对象指针`T*` | `remove_cv_t<T>` |
| 数组`T[N]`或`T[]` | 去除一层数组及元素cv后的类型 |
| 只有成员`value_type`的类 | 该成员去除cv后的对象类型 |
| 只有成员`element_type`的类 | 该成员去除cv后的对象类型 |
| 两个成员都有的类 | 二者去除cv后相同才提供该对象类型；不同则没有`value_type` |

可通过公开类型查询选定结果：

```cpp
using pointer_value = asc::std::indirectly_readable_traits<int*>::value_type;
using array_value = asc::std::indirectly_readable_traits<const int[3]>::value_type;
```

其他类型或不能确定对象类型的分支不提供该成员。

## 约束说明

- 提供C++20公开迭代器概念和特征接口。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>
#include <asc/std/type_traits>

bool example()
{
    struct element_holder { using element_type = const long; };
    using pointer_value = asc::std::indirectly_readable_traits<int*>::value_type;
    using array_value = asc::std::indirectly_readable_traits<const int[3]>::value_type;
    using member_value = asc::std::indirectly_readable_traits<element_holder>::value_type;
    static_assert(asc::std::is_same_v<pointer_value, int>);
    static_assert(asc::std::is_same_v<array_value, int>);
    static_assert(asc::std::is_same_v<member_value, long>);
    return true;
}
```

## 关联API

- [`asc::std::indirectly_readable_traits`](indirectly_readable_traits.md)
- [本头文件的接口列表](asc_std_iterator.md)
