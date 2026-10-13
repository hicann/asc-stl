# asc::std::basic_string::begin

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

头文件路径为：`<asc/std/string>`。

`asc::std::basic_string::begin`返回指向首元素的迭代器。

标准语义参考：[cppreference `string`](https://en.cppreference.com/w/cpp/header/string)。

## 函数原型

所属类型：[`asc::std::basic_string`](basic_string.md)。

### 原型1

```cpp
// asc::std::basic_string 类内的声明节选；模板形参和其他成员由所属类提供。
const_iterator begin() const noexcept;
```

### 原型2

```cpp
// asc::std::basic_string 类内的声明节选；模板形参和其他成员由所属类提供。
iterator begin() noexcept;
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

无参数。

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `const_iterator` | 返回指向首元素的迭代器。 |
| 原型2 | `iterator` | 返回指向首元素的迭代器。 |

## 约束说明

- basic_string<char,Traits,A>显式allocator构造。
- plain/local字符来源的append/push_back/clear。
- size/capacity/data/c_str/迭代/索引与析构。
- 仅容量充足和不抛出异常域。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <memory>
#include <string>
#include <asc/std/string>

bool example()
{
    using string_type = asc::std::basic_string<char, ::std::char_traits<char>, ::std::allocator<char>>;
    string_type text(::std::allocator<char>{});
    text += "hi";
    return *text.begin() == 'h';
}
```

## 关联API

- [`asc::std::basic_string`](basic_string.md)
- [本头文件的接口列表](asc_std_string.md)
