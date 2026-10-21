# asc::std::make_index_sequence

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

头文件路径为：`<asc/std/utility>`。

`asc::std::make_index_sequence`在编译期生成或保存整数索引序列类型。

标准语义参考：[cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility)。

## 声明

```cpp
namespace asc::std {
template<size_t N> using make_index_sequence = make_integer_sequence<size_t, N>;
} // namespace asc::std
```

## 约束说明

- 提供完整的标准形式。

## 调用示例

以下Host示例用具体类型和独立预期检查别名或标记结果。

```cpp
#include <asc/std/utility>
#include <asc/std/type_traits>

void use_type()
{
    using selected = asc::std::make_index_sequence<3>;
    static_assert(asc::std::is_same_v<selected, asc::std::index_sequence<0, 1, 2>>);
}
```

## 关联API

- [本头文件的接口列表](asc_std_utility.md)
