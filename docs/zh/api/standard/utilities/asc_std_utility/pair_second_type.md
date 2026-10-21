# asc::std::pair::second_type

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

`asc::std::pair::second_type`标识pair的对应元素类型。

标准语义参考：[cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility)。

## 声明

所属类型：[`asc::std::pair`](pair.md)。

```cpp
// asc::std::pair 类内的声明节选；模板形参和其他成员由所属类提供。
using second_type = T2;
```

## 约束说明

- 异常规格以对应声明为准；Device侧使用的元素操作须不抛出异常。
- pair的直接自由比较入口为`operator==`和`operator<`；其他关系辅助位于`rel_ops`。

## 调用示例

以下Host示例用具体类型和独立预期检查别名或标记结果。

```cpp
#include <asc/std/utility>
#include <asc/std/type_traits>

void use_type()
{
    using alias_type = typename asc::std::pair<int, int>::second_type;
    static_assert(asc::std::is_same_v<alias_type, int>);
}
```

## 关联API

- [`asc::std::pair`](pair.md)
- [本头文件的接口列表](asc_std_utility.md)
