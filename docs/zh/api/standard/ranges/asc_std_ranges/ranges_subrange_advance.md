# asc::std::ranges::subrange::advance

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

`asc::std::ranges::subrange::advance`把当前子范围的起始位置推进指定距离。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

所属类型：[`subrange`](ranges_subrange.md)。以下省略SFINAE选择参数。next的const左值形式要求forward_iterator<It>；prev要求bidirectional_iterator<It>；It默认为Iter。距离类型为实现平台的ptrdiff_t。

### 原型1

```cpp
constexpr subrange& advance(ptrdiff_t amount);
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `amount` | 输入 | 有符号位置偏移，单位为迭代步数；无默认值。正数前进，负数要求底层迭代器可双向移动。 |

## 返回值说明

返回*this，原地更新起点及适用的已保存数量。

## 约束说明

- 向正方向移动在原end处停止；负向移动须有bidirectional_iterator，且不得越过可达的底层起始边界。
- amount及向iter_difference_t<Iter>的转换须可表示；prev还要求取负运算有效。
- 结果仍借用原存储，不延长元素生命周期。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/ranges>

bool example()
{
    int values[4] = {1, 2, 3, 4};
    asc::std::ranges::subrange<int*> view(values + 1, values + 4);
    view.advance(1);
    return *view.begin() == 3 && view.size() == 2;
}
```

## 关联API

- [`asc::std::ranges::subrange`](ranges_subrange.md)
- [本头文件的接口列表](asc_std_ranges.md)
