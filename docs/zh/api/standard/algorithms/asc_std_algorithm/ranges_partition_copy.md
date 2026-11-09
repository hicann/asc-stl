# asc::std::ranges::partition_copy

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

头文件路径为 `<asc/std/algorithm>`。按投影后的谓词结果稳定复制到两个输出范围。接口以 C++17 起可调用的常量函数对象提供。

## 声明

以下给出已交付的调用形式；对象的实现类型不是接口承诺。省略的投影参数使用 `asc::std::identity`。

```cpp
namespace asc::std::ranges {
partition_copy(first, last, yes, no, pred, projection = {});
}  // namespace asc::std::ranges
```

```cpp
namespace asc::std::ranges {
partition_copy(range, yes, no, pred, projection = {});
}  // namespace asc::std::ranges
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入起始迭代器。 |
| `last` | 输入 | 输入结束哨兵。 |
| `yes` | 输出 | 满足谓词时写入的输出起点。 |
| `no` | 输出 | 不满足谓词时写入的输出起点。 |
| `pred` | 输入 | 接收投影结果的判断函数。 |
| `projection` | 输入 | 作用于输入元素的投影。 |
| `range` | 输入 | 要访问的范围；非拥有返回值受其生命周期约束。 |

## 返回值说明

`partition_copy_result<Iterator, Output1, Output2>`. in 为输入末迭代器；out1/out2 分别为满足与不满足谓词的输出末位置。

## 约束说明

迭代器与哨兵须形成有效范围，输出空间须足够。可调用对象、投影、写入或移动操作须满足对应算法的类型约束。接口不拥有输入或输出存储，不延长范围生命周期，也不提供设备线程间同步。 非借用临时范围不返回可解引用的输入迭代器，而返回 `dangling`；借用范围的返回位置只能在底层存储有效期间使用。 C++17 传统输出适配器若不满足递增约束，应使用可写迭代器或 C++20 输出适配器。

## 调用示例

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[] = {1, 2, 3, 4}, yes[4]{}, no[4]{};
    auto result = asc::std::ranges::partition_copy(values, yes, no, [](int value) { return value % 2 == 0; });
    return result.out1 == yes + 2 && result.out2 == no + 2 && yes[0] == 2 && no[1] == 3;
}
```

## 关联API

- [<asc/std/algorithm>](asc_std_algorithm.md)
