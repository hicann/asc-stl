# asc::std::ranges::views::drop

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

头文件路径为：`<asc/std/ranges>`。

`asc::std::ranges::views::drop`跳过输入范围起始处指定数量的元素。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 声明

该公开名称为常量可调用对象，不是自由函数；其实现类不属于公开契约。以下仅查询对象类型，object_type是示例名称。调用形式见参数说明及示例。

```cpp
using object_type = decltype(asc::std::ranges::views::drop);
```

## 参数说明

### 调用形式1的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `range` | 输入 | 待访问或变换的输入范围；借用结果受其生命周期约束。 |
| `count` | 输入 | 要处理、保留或跳过的元素数量。 |

### 调用形式2的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `count` | 输入 | 要处理、保留或跳过的元素数量。 |

## 返回值说明

empty_view直接返回原空视图类型。随机访问且有大小的span、basic_string_view、iota_view及适用subrange使用直通重建，span结果可改为动态extent；repeat_view调整次数或保留无界形式。其它输入返回drop_view<views::all_t<Range>>。

精确结果类型可用`decltype(asc::std::ranges::views::drop(输入, 数量))`在对应输入类型上查询；不能统一写成一个包装view类型。

## 约束说明

- 输入及返回对象须满足所选择分支的范围、迭代器和构造条件；返回类型按上述条件选择。
- 数量须非负且可由范围差值类型表示；有界范围截断到实际长度，不访问尾后元素。
- 视图沿用原范围的持有方式，借用的元素存储须覆盖实际访问期。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/ranges>
#include <asc/std/span>
#include <asc/std/type_traits>

bool example()
{
    int values[4] = {1, 2, 3, 4};
    asc::std::span<int> base(values);
    auto result = asc::std::ranges::views::drop(base, 2);
    static_assert(asc::std::is_same_v<decltype(result), asc::std::span<int>>);
    return result.size() == 2 && result[0] == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
