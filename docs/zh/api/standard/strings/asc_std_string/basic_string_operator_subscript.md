# asc::std::basic_string::operator[]

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

`asc::std::basic_string::operator[]` 在调用方保证索引有效时访问指定元素。

标准语义参考：[cppreference `string`](https://en.cppreference.com/w/cpp/header/string)。

## 函数原型

### 原型 1

```cpp
const_reference asc::std::basic_string::operator[](size_type index) const noexcept;
```

### 原型 2

```cpp
reference asc::std::basic_string::operator[](size_type index) noexcept;
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `index` | 输入 | 提供“在调用方保证索引有效时访问指定元素”所需的输入对象；类型须满足所选原型约束。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `index` | 输入 | 提供“在调用方保证索引有效时访问指定元素”所需的输入对象；类型须满足所选原型约束。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `const_reference` | 返回指定索引处的元素引用或代理值；索引必须有效。 |
| 原型 2 | `reference` | 返回指定索引处的元素引用或代理值；索引必须有效。 |

## 约束说明

- basic_string<char,Traits,A>显式allocator构造
- plain/local字符来源的append/push_back/clear
- size/capacity/data/c_str/迭代/索引与析构
- 仅容量充足和不抛出异常域

## 调用示例

以下 Host 片段使用显式提供的分配器；设备端须使用在目标执行位置可调用的分配器。

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
    if (!value.empty())
        return value[0];
}
```
