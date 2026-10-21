# asc::std::insert_iterator::`operator=`

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

`asc::std::insert_iterator::operator=`按所选赋值重载更新对象，并返回规定的结果。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

所属类型：[`asc::std::insert_iterator`](insert_iterator.md)。

### 原型1

```cpp
// asc::std::insert_iterator 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr insert_iterator<Container>& operator=(const typename Container::value_type& value);
```

### 原型2

```cpp
// asc::std::insert_iterator 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr insert_iterator<Container>& operator=(typename Container::value_type&& value);
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待插入到容器当前插入位置的元素值；调用`container->insert(iter, value)`复制插入，并将保存位置更新为返回位置的后一位置。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待插入到容器当前插入位置的元素值；调用`container->insert(iter, asc::std::move(value))`移动插入，并将保存位置更新为返回位置的后一位置；值的移动后状态遵守其类型约定。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `insert_iterator<Container> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型2 | `insert_iterator<Container> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

## 约束说明

- 目标容器须支持对应的`insert(position, value)`操作；插入迭代器保存容器地址，不拥有容器。
- 容器须在适配器使用期间有效；插入操作还须遵守目标容器自身的迭代器失效规则。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>
#include <vector>

bool example()
{
    ::std::vector<int> values;
    asc::std::insert_iterator<::std::vector<int>> output(values, values.begin());
    *output = 7;
    *output = 9;
    return values.size() == 2 && values[0] == 7 && values[1] == 9;
}
```

## 关联API

- [`asc::std::insert_iterator`](insert_iterator.md)
- [本头文件的接口列表](asc_std_iterator.md)
