# asc::std::char_traits

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

`asc::std::char_traits`定义字符比较、复制和长度计算的操作策略。

标准语义参考：[cppreference `string_view`](https://en.cppreference.com/w/cpp/header/string_view)。

## 声明

```cpp
namespace asc::std {
template<class CharT> class char_traits;
} // namespace asc::std
```

## 约束说明

- 提供构造、迭代和除at外的访问接口，以及remove_prefix、remove_suffix、swap、data、size、starts_with、ends_with和非抛出的比较/查找接口。
- AI Core SIMD编程 仅支持local或generic地址空间的普通字符指针。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/string_view>

bool example()
{
    const char text[] = "hello";
    return asc::std::char_traits<char>::length(text) == 5 && asc::std::char_traits<char>::eq(text[0], 'h');
}
```

## 关联API

- [本头文件的接口列表](asc_std_string_view.md)
