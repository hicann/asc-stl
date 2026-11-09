# asc::std::ranges::transform

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

头文件路径为 `<asc/std/algorithm>`。对投影后的输入执行一元或二元变换，并写入输出范围。接口以 C++17 起可调用的常量函数对象提供。

## 声明

以下给出已交付的调用形式；对象的实现类型不是接口承诺。省略的投影参数使用 `asc::std::identity`。

```cpp
namespace asc::std::ranges {
transform(first, last, out, function, projection = {});
}  // namespace asc::std::ranges
```

```cpp
namespace asc::std::ranges {
transform(range, out, function, projection = {});
}  // namespace asc::std::ranges
```

```cpp
namespace asc::std::ranges {
transform(first1, last1, first2, last2, output, function, projection1 = {}, projection2 = {});
}  // namespace asc::std::ranges
```

```cpp
namespace asc::std::ranges {
transform(range1, range2, output, function, projection1 = {}, projection2 = {});
}  // namespace asc::std::ranges
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入起始迭代器。 |
| `last` | 输入 | 输入结束哨兵。 |
| `out` | 输出 | 写入结果的起始位置。 |
| `function` | 输入 | 执行变换或累积的可调用对象。 |
| `projection` | 输入 | 作用于输入元素的投影。 |
| `range` | 输入 | 要访问的范围；非拥有返回值受其生命周期约束。 |
| `first1` | 输入 | 第一个输入的起始迭代器。 |
| `last1` | 输入 | 第一个输入的结束哨兵。 |
| `first2` | 输入 | 第二个输入的起始迭代器。 |
| `last2` | 输入 | 第二个输入的结束哨兵。 |
| `output` | 输出 | 写入结果的起始位置。 |
| `projection1` | 输入 | 第一个输入的投影。 |
| `projection2` | 输入 | 第二个输入的投影。 |
| `range1` | 输入 | 第一个输入范围。 |
| `range2` | 输入 | 第二个输入范围。 |

## 返回值说明

`unary_transform_result<Iterator, Output> / binary_transform_result<Iterator1, Iterator2, Output>`. 一元结果包含 in/out，二元结果包含 in1/in2/out；二元变换在任一输入范围结束时停止。

## 约束说明

迭代器与哨兵须形成有效范围，输出空间须足够。可调用对象、投影、写入或移动操作须满足对应算法的类型约束。接口不拥有输入或输出存储，不延长范围生命周期，也不提供设备线程间同步。 非借用临时范围不返回可解引用的输入迭代器，而返回 `dangling`；借用范围的返回位置只能在底层存储有效期间使用。 C++17 传统输出适配器若不满足递增约束，应使用可写迭代器或 C++20 输出适配器。

## 调用示例

```cpp
#include <asc/std/algorithm>

bool example()
{
    int left[] = {1, 2, 3}, right[] = {4, 5}, output[3]{};
    auto result = asc::std::ranges::transform(left, right, output, [](int x, int y) { return x + y; });
    return result.in1 == left + 2 && result.in2 == right + 2 && result.out == output + 2 && output[0] == 5 && output[1] == 7;
}
```

## 关联API

- [<asc/std/algorithm>](asc_std_algorithm.md)
