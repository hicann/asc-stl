# asc::std::counted_iterator::`operator*`

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

`asc::std::counted_iterator::operator*`解引用当前迭代器或有值对象。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

所属类型：[`asc::std::counted_iterator`](counted_iterator.md)。

### 原型1

```cpp
// counted_iterator 类内声明节选。
constexpr decltype(auto) operator*();
```

### 原型2

```cpp
// counted_iterator 类内声明节选。
template<class I2 = Iter>
constexpr decltype(auto) operator*() const;
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `I2` | 成员选择类型，默认为所属类的`Iter`；须满足本原型的表达式或遍历要求。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `decltype(auto)` | 返回当前迭代器、范围或字符串所指位置的元素引用或代理值。 |
| 原型2 | `decltype(auto)` | 返回当前迭代器、范围或字符串所指位置的元素引用或代理值。 |

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
    return *iterator == 2;
}
```

## 关联API

- [`asc::std::counted_iterator`](counted_iterator.md)
- [本头文件的接口列表](asc_std_iterator.md)
