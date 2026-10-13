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

所属类型：[`asc::std::move_sentinel`](move_sentinel.md)。

```cpp
// asc::std::move_sentinel 类内的声明节选；模板形参和其他成员由所属类提供。
template<class S2> constexpr move_sentinel<Sent>& operator=(const move_sentinel<S2>& other);
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `S2` | 来源哨兵的类型；须满足到当前哨兵类型的转换条件。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 赋值来源对象；左值形式复制其状态，右值形式按对应成员的移动操作转移状态。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `move_sentinel<Sent> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

## 约束说明

- 使用调用方提供的迭代器或容器。
- pair的直接自由比较入口为`operator==`和`operator<`；其他关系辅助位于`rel_ops`。

## 调用示例

以下Host片段以具体指针迭代器演示调用；调用方须保证所指范围及移动后位置有效。

```cpp
#include <asc/std/iterator>

void example(asc::std::move_sentinel<const int*>& destination, const asc::std::move_sentinel<int*>& source)
{
    destination = source;
}
```

## 关联API

- [`asc::std::move_sentinel`](move_sentinel.md)
- [本头文件的接口列表](asc_std_iterator.md)
