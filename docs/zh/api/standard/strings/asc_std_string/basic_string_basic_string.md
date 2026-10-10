# asc::std::basic_string::basic_string

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

`asc::std::basic_string::basic_string` 按本页所列构造形态初始化 `basic_string` 对象。

标准语义参考：[cppreference `string`](https://en.cppreference.com/w/cpp/header/string)。

## 函数原型

### 原型 1

```cpp
basic_string(const Allocator& allocator) noexcept;
```

### 原型 2

```cpp
basic_string(const CharT* pointer, const Allocator& allocator);
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 提供“按本页所列构造形态初始化 `basic_string` 对象”所需的数据地址；可访问范围和生命周期须满足约束。 |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

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

void example()
{
    example_allocator<char> allocator{};
    asc::std::basic_string<char, ::std::char_traits<char>, example_allocator<char>> value(allocator);
    (void)value.size();
}
```
