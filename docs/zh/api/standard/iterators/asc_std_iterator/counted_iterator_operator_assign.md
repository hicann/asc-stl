# asc::std::counted_iterator::`operator=`

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

`asc::std::counted_iterator::operator=`按所选赋值重载更新对象，并返回规定的结果。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

所属类型：[`counted_iterator`](counted_iterator.md)。以下保留转换赋值的真实参与条件；C++17及Device以SFINAE选择，Host C++20以相同的requires条件选择。

```cpp
template<class I2, enable_if_t<assignable_from<Iter&, const I2&>, int> = 0>
constexpr counted_iterator& operator=(const counted_iterator<I2>& other) noexcept(is_nothrow_assignable_v<Iter&, const I2&>);
```

同类型特殊成员赋值按C++隐式声明规则处理。

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `I2` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 转换赋值来源，形参为const引用；保存的底层状态须满足原型给出的转换和赋值条件。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `counted_iterator&` | 从来源复制当前底层位置及剩余计数，返回*this；来源保持有效。 |

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
    asc::std::counted_iterator<const int*> target;
    target = iterator;
    return *target == 2;
}
```

## 关联API

- [`asc::std::counted_iterator`](counted_iterator.md)
- [本头文件的接口列表](asc_std_iterator.md)
