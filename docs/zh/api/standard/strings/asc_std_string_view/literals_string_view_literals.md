# asc::std::literals::string_view_literals

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

头文件路径为：`<asc/std/string_view>`。

`asc::std::literals::string_view_literals`组织对应字符串视图字面量运算符的公开命名空间。

标准语义参考：[cppreference `string_view`](https://en.cppreference.com/w/cpp/header/string_view)。

## 声明

```cpp
namespace asc::std {
inline namespace literals {
inline namespace string_view_literals {}
}
}
```

## 约束说明

- 组织sv字面量运算符；各字符类型的字面量生成对应basic_string_view，不提供视图成员函数。视图借用字符串字面量的静态存储。
- AI Core SIMD编程 仅支持local或generic地址空间的普通字符指针。

## 调用示例

以下Host示例给出具体输入并检查结果；底层对象与存储在检查期间仍有效。

```cpp
#include <asc/std/string_view>

bool example()
{
    constexpr auto value = asc::std::literals::string_view_literals::operator""sv("abc", 3);
    static_assert(value.size() == 3 && value[1] == 'b');
    return true;
}
```

## 关联API

- [本头文件的接口列表](asc_std_string_view.md)
