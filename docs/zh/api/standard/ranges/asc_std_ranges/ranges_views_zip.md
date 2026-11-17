# asc::std::ranges::views::zip

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

`asc::std::ranges::views::zip`将恰好两个可确定大小的随机访问范围按位置配对，所得视图在较短的输入范围结束时结束。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 声明

该名称是公开的常量函数对象；对象的实现类型不构成接口承诺。以下为调用形式，省略的可选参数以各原型约束为准。

```cpp
// asc::std::ranges::views 类内的声明节选；模板形参和其他成员由所属类提供。
zip(first_range, second_range);
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first_range` | 输入 | 第一个待组合的输入范围。 |
| `second_range` | 输入 | 第二个待组合的输入范围。 |

## 返回值说明

返回同步遍历两个输入范围的视图，长度由较短的输入范围决定。

| 调用形式 | 返回类型 |
| --- | --- |
| 两个范围 | `zip_view<decltype(views::all(first_range)), decltype(views::all(second_range))>` |

## 约束说明

- 本期支持恰好两个随机访问且有大小的范围，可在Host以及设备侧SIMD和SIMT编程中使用。
- 随机访问能力按迭代器的现代`iterator_concept`判定；值返回的`transform_view`即使传统`iterator_category`为输入迭代器标签，仍可保留随机访问遍历能力并参与zip。
- 解引用所得tuple逐项保留底层解引用类型：引用可向可写元素写回，按值返回的变换结果则存为值。借用的底层存储须覆盖全部访问期。
- 迭代器支持默认构造，可与符合约束的`ranges`算法组合；输出空间仍由调用者提供，zip不分配输出缓冲区。
- const迭代要求两侧可const遍历，且各自const迭代器类型与非const形式相同。

## 调用示例

以下Host示例实现候选分数校正：先惰性缩放score，再与correction按位置配对，写出校正分数供后续阈值筛选。两路长度不等时只处理较短的一路，不读取缺失的correction，也不覆盖输出尾部。

```cpp
#include <asc/std/ranges>
#include <asc/std/algorithm>
#include <asc/std/tuple>

bool example()
{
    int scores[] = {1, 6, -4, 3, 8};
    int correction[] = {0, -2, 7, 0};
    int calibrated[5] = {-99, -99, -99, -99, -99};
    auto scaled = scores | asc::std::ranges::views::transform([](int value) { return value * 2; });
    auto paired = asc::std::ranges::views::zip(scaled, correction);
    auto result = asc::std::ranges::transform(paired, calibrated, [](auto values) {
        return asc::std::get<0>(values) + asc::std::get<1>(values);
    });
    return result.out == calibrated + 4 && calibrated[0] == 2 && calibrated[1] == 10 &&
        calibrated[2] == -1 && calibrated[3] == 6 && calibrated[4] == -99;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
