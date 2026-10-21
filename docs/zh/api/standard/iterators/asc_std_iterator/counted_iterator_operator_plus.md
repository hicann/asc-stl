# asc::std::counted_iterator::`operator+`

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

`asc::std::counted_iterator::operator+`按该类型定义的加法或位移规则产生新值。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

所属类型：[`asc::std::counted_iterator`](counted_iterator.md)。

```cpp
// counted_iterator 类内声明节选；类模板参数和其余成员由所属类提供。
template<class I2 = Iter, enable_if_t<random_access_iterator<I2>, int> = 0>
constexpr counted_iterator operator+(iter_difference_t<I2> count) const;
```

以上为C++17及Device选择形式；Host C++20以`requires random_access_iterator<I2>`表达相同参与条件。

### 对称非成员形式

```cpp
namespace asc::std {
template<class Iter>
[[nodiscard]] constexpr counted_iterator<Iter> operator+(typename counted_iterator<Iter>::difference_type count,
    const counted_iterator<Iter>& value);
}
```

这是与成员加法对应的命名空间非成员模板，以count+value调用。

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `I2` | 成员选择类型，默认为所属类的`Iter`；须满足本原型的表达式或遍历要求。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `count` | 输入 | 参与操作的元素数量。 |

对称形式的count为有符号距离，value为源适配器的const引用；返回与value+count相同的新适配器，不改变value。底层须支持对应随机访问位移。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `counted_iterator<Iter>` | 返回按指定距离移动后的新迭代器，原迭代器保持不变。 |

## 约束说明

- `Iter`须满足本操作要求的遍历能力；适配器不拥有底层范围。
- `count()`表示从当前位置开始剩余的元素数量；解引用及自增要求剩余数量大于0。
- 位移后的底层位置及对应计数须有效，不得越过实际有效范围。
- 本页的位移或下标成员要求底层迭代器满足随机访问迭代器要求。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4, 6, 8};
    asc::std::counted_iterator<int*> iterator(values, 4);
    auto result = iterator + 1;
    auto symmetric = 1 + iterator;
    return *result == 4 && *iterator == 2 && symmetric.base() == result.base();
}
```

## 关联API

- [`asc::std::counted_iterator`](counted_iterator.md)
- [本头文件的接口列表](asc_std_iterator.md)
