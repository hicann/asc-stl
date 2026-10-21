# asc::std::ranges::equal_to::is_transparent

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

头文件路径为：`<asc/std/functional>`。

`asc::std::ranges::equal_to::is_transparent`标记函数对象支持异构参数类型的透明调用。

标准语义参考：[cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional)。

## 声明

所属类型：[`asc::std::ranges::equal_to`](ranges_equal_to.md)。

```cpp
// asc::std::ranges::equal_to 类内的声明节选；模板形参和其他成员由所属类提供。
using is_transparent = void;
```

## 约束说明

- 同时提供指定类型形式和透明调用形式。

## 调用示例

以下Host示例用具体类型和独立预期检查别名或标记结果。

```cpp
#include <asc/std/functional>
#include <asc/std/type_traits>

void use_type()
{
    using alias_type = asc::std::ranges::equal_to::is_transparent;
    static_assert(asc::std::is_same_v<alias_type, void>);
}
```

## 关联API

- [`asc::std::ranges::equal_to`](ranges_equal_to.md)
- [本头文件的接口列表](asc_std_functional.md)
