# asc::std::basic_string::`operator+=`

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

`asc::std::basic_string::operator+=`在当前字符串末尾追加操作数，并返回当前字符串的引用：原型1追加单个字符`value`；原型2追加以空字符结尾的字符串`text`。

标准语义参考：[cppreference `string`](https://en.cppreference.com/w/cpp/header/string)。

## 函数原型

所属类型：[`asc::std::basic_string`](basic_string.md)。

### 原型1

```cpp
// asc::std::basic_string 类内的声明节选；模板形参和其他成员由所属类提供。
basic_string<CharT, Traits, Allocator>& operator+=(CharT value);
```

### 原型2

```cpp
// asc::std::basic_string 类内的声明节选；模板形参和其他成员由所属类提供。
basic_string<CharT, Traits, Allocator>& operator+=(const CharT* text);
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 追加到当前字符串末尾的单个字符。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `text` | 输入 | 追加到当前字符串末尾、以空字符结尾的字符串首地址；可访问范围和生命周期须满足约束。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `basic_string<CharT, Traits, Allocator> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型2 | `basic_string<CharT, Traits, Allocator> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

## 约束说明

- basic_string<char,Traits,A>显式allocator构造。
- plain/local字符来源的append/push_back/clear。
- size/capacity/data/c_str/迭代/索引与析构。
- 仅容量充足和不抛出异常域。

## 调用示例

以下Host片段使用显式提供的分配器；设备端须使用在目标执行位置可调用的分配器。

```cpp
#include <asc/std/string>
#include <functional>
#include <memory>
#include <string>
#include <utility>

template <class T>
struct example_allocator : ::std::allocator<T> {
    using value_type = T;
    using pointer = T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template <class U> struct rebind { using other = example_allocator<U>; };
    example_allocator() = default;
    template <class U> example_allocator(const example_allocator<U>&) noexcept {}
};

decltype(auto) example(asc::std::basic_string<char, ::std::char_traits<char>, example_allocator<char>>& value)
{
    return (value += 'a');
}
```

## 关联API

- [`asc::std::basic_string`](basic_string.md)
- [本头文件的接口列表](asc_std_string.md)
