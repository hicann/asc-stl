# asc::std::move_sentinel::`operator=`

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

`asc::std::move_sentinel::operator=`按所选赋值重载更新对象，并返回规定的结果。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

所属类型：[`move_sentinel`](move_sentinel.md)。以下保留转换赋值的真实参与条件；C++17及Device以SFINAE选择，Host C++20以相同的requires条件选择。

```cpp
template<class S2, enable_if_t<assignable_from<Sent&, const S2&>, int> = 0>
constexpr move_sentinel& operator=(const move_sentinel<S2>& other);
```

同类型特殊成员赋值按C++隐式声明规则处理。

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `S2` | 来源哨兵的类型；须满足到当前哨兵类型的转换条件。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 转换赋值来源，形参为const引用；保存的底层状态须满足原型给出的转换和赋值条件。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `move_sentinel&` | 从来源保存的底层结束标记更新目标，返回*this；来源不因本转换赋值而改变。 |

## 约束说明

- 哨兵类型须支持对应构造、转换或赋值操作，并可与配套底层迭代器比较。
- 哨兵不拥有底层范围，也不能解引用；其结束标记须在比较期间有效。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4};
    asc::std::move_sentinel<int*> sentinel(values + 2);
    asc::std::move_iterator<int*> iterator(values);
    asc::std::move_sentinel<const int*> target;
    target = sentinel;
    return target.base() == values + 2;
}
```

## 关联API

- [`asc::std::move_sentinel`](move_sentinel.md)
- [本头文件的接口列表](asc_std_iterator.md)
