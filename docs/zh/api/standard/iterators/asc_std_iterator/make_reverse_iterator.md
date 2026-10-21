# asc::std::make_reverse_iterator

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

`asc::std::make_reverse_iterator`创建逆序遍历的迭代器适配器。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

```cpp
namespace asc::std {
template<class Iter> constexpr reverse_iterator<Iter> make_reverse_iterator(Iter value) noexcept(is_nothrow_copy_constructible_v<Iter>);
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Iter` | 被适配的基础迭代器类型；须至少满足双向迭代器要求。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 被包装的基础迭代器；通常传入范围尾后迭代器，适配器自该位置起逆序向前遍历。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `reverse_iterator<Iter>` | 返回保存调用方参数的迭代器适配器；底层范围须在使用期间保持有效。 |

## 约束说明

- 底层迭代器须支持双向遍历；随机访问成员还要求底层支持对应位移或下标运算。
- 反向迭代器访问`base()`之前的元素，解引用或箭头访问要求该前一位置有效。
- 适配器不拥有底层范围；返回引用或指针的寿命受底层对象约束。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {1, 2, 3, 4};
    auto result = asc::std::make_reverse_iterator(values + 4);
    return result.base() == values + 4 && *result == 4;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
