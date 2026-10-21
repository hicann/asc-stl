# asc::std::cbegin

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

`asc::std::cbegin`取得范围起始常量迭代器。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

`asc::std::cbegin`是可调用对象，使用`asc::std::cbegin(range)`调用。以下通过公开对象查询类型，并列出调用运算符摘要。

```cpp
namespace asc::std {
// 查询公开对象的类型；对象及其调用运算符由头文件提供。
using cbegin_object_type = decltype(::asc::std::cbegin);
}
```

### 原型1

```cpp
// 可调用对象类型的类内声明节选。
template<class C>
constexpr auto operator()(const C& c) const
    noexcept(noexcept(::asc::std::begin(c))) -> decltype(::asc::std::begin(c));
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `C` | 被查询数组或容器的类型，须提供对应的范围访问操作。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `c` | 输入 | 提供“取得范围起始常量迭代器”使用的对象引用；被引用对象须在调用期间有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `decltype(asc::std::begin(c))` | 返回范围起始常量迭代器。 |

## 约束说明

- 容器形式要求对应const或非const成员访问表达式有效；内建数组形式保留元素类型和const限定。
- 对象返回的迭代器不拥有范围，使用期间底层容器或数组须保持有效。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {1, 2, 3, 4};
    auto first = asc::std::cbegin(values);
    return first == values && *first == 1;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
