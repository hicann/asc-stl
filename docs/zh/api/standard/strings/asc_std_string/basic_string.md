# asc::std::basic_string

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

`asc::std::basic_string`拥有并管理连续字符序列。

标准语义参考：[cppreference `string`](https://en.cppreference.com/w/cpp/header/string)。

## 声明

```cpp
namespace asc::std {
template<class CharT, class Traits, class Allocator> class basic_string;
} // namespace asc::std
```

## 约束说明

- basic_string<char,Traits,A>显式allocator构造。
- plain/local字符来源的append/push_back/clear。
- size/capacity/data/c_str/迭代/索引与析构。
- 仅容量充足和不抛出异常域。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <memory>
#include <string>
#include <asc/std/string>

bool example()
{
    using string_type = asc::std::basic_string<char, ::std::char_traits<char>, ::std::allocator<char>>;
    string_type text(::std::allocator<char>{});
    text += "hi";
    return text.size() == 2 && text[0] == 'h' && text[1] == 'i';
}
```

## 关联API

- [本头文件的接口列表](asc_std_string.md)
