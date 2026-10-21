# asc::std::make_move_iterator

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

`asc::std::make_move_iterator`创建解引用时以右值引用访问元素的迭代器适配器。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

```cpp
namespace asc::std {
template<class Iter> constexpr move_iterator<Iter> make_move_iterator(Iter iterator) noexcept(is_nothrow_move_constructible_v<Iter>);
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Iter` | 被包装或移动的底层迭代器类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `iterator` | 输入 | 指向本次操作位置的迭代器；所指范围须在调用期间有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `move_iterator<Iter>` | 返回保存调用方参数的迭代器适配器；底层范围须在使用期间保持有效。 |

## 约束说明

- 底层迭代器须支持本页操作；自减要求双向遍历，位移和下标要求相应随机访问操作。
- 适配器不拥有底层元素；解引用通过`asc::std::iter_move`访问元素，移动后的值遵守元素类型的约定。
- 解引用、箭头及下标访问须指向有效元素；返回引用或指针的寿命受底层对象约束。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {1, 2, 3, 4};
    auto result = asc::std::make_move_iterator(values);
    return result.base() == values && *result == 1;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
