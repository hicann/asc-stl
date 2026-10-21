# asc::std::counted_iterator::`operator++`

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

`asc::std::counted_iterator::operator++`把当前迭代器或计数值推进一步。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

所属类型：[`asc::std::counted_iterator`](counted_iterator.md)。

```cpp
// counted_iterator 类内声明节选；类模板参数和其余成员由所属类提供。
constexpr counted_iterator& operator++();
```

后置自增只有一个成员模板，以下两个条件分支互斥：

```cpp
// counted_iterator 类内声明节选。
#if CANN_ASC_STL_DETAIL_HAS_EXCEPTIONS() && !CANN_ASC_STL_DETAIL_HAS_CXX20()
template<class I2 = Iter>
auto operator++(int);
#else
template<class I2 = Iter>
constexpr auto operator++(int);
#endif
```

## 参数说明

前置形式无参数。后置形式的`int`为区分语法的占位参数，通常写作`iterator++`。

| 模板参数 | 描述 |
| --- | --- |
| `I2` | 后置形式的选择类型，默认等于所属类的`Iter`；通常由默认值提供。 |

## 返回值说明

前置形式返回递增后当前适配器的引用。后置形式在底层满足前向迭代器要求时，返回递增前的`counted_iterator`副本；否则返回底层`current_++`的结果，其类型由底层迭代器决定。

两种形式成功后都将当前位置前移一位，并将剩余计数减1。带异常支持的非前向分支在底层后置递增抛出异常时恢复原计数。

## 约束说明

- `Iter`须满足本操作要求的遍历能力；适配器不拥有底层范围。
- `count()`表示从当前位置开始剩余的元素数量；解引用及自增要求剩余数量大于0。
- 位移后的底层位置及对应计数须有效，不得越过实际有效范围。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4, 6, 8};
    asc::std::counted_iterator<int*> iterator(values, 4);
    auto old = iterator++;
    return *old == 2 && *iterator == 4;
}
```

## 关联API

- [`asc::std::counted_iterator`](counted_iterator.md)
- [本头文件的接口列表](asc_std_iterator.md)
