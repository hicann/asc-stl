# asc::std::u8string_view

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

`asc::std::u8string_view`提供相应字符类型的非拥有字符串视图别名。

该接口自C++20+ 模式起提供。

标准语义参考：[cppreference `string_view`](https://en.cppreference.com/w/cpp/header/string_view)。

## 声明

```cpp
namespace asc::std {
using u8string_view = basic_string_view<char8_t>;
} // namespace asc::std
```

## 约束说明

- 本类型不拥有字符存储。原字符数组或字符串的存储须覆盖视图、指针和迭代器的全部使用期间；原存储销毁或因重分配失效后，不能继续通过视图访问。

- 提供构造、迭代和除at外的访问接口，以及remove_prefix、remove_suffix、swap、data、size、starts_with、ends_with和非抛出的比较/查找接口。
- AI Core SIMD编程 仅支持local或generic地址空间的普通字符指针。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/string_view>

bool example()
{
    asc::std::u8string_view text(u8"abc");
    return text.size() == 3 && text[1] == u8'b';
}
```

## 关联API

- [本头文件的接口列表](asc_std_string_view.md)
