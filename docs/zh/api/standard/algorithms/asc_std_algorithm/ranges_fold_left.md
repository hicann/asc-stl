# asc::std::ranges::fold_left

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

头文件路径为 `<asc/std/algorithm>`。从初值开始，严格从左到右累积输入范围。接口以 C++17 起可调用的常量函数对象提供。

## 声明

以下给出已交付的调用形式；对象的实现类型不是接口承诺。

```cpp
namespace asc::std::ranges {
fold_left(first, last, init, function);
}  // namespace asc::std::ranges
```

```cpp
namespace asc::std::ranges {
fold_left(range, init, function);
}  // namespace asc::std::ranges
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入起始迭代器。 |
| `last` | 输入 | 输入结束哨兵。 |
| `init` | 输入 | 按值传入的累积初值。 |
| `function` | 输入 | 执行变换或累积的可调用对象。 |
| `range` | 输入 | 要访问的范围；非拥有返回值受其生命周期约束。 |

## 返回值说明

`decay_t<invoke_result_t<Function&, T, iter_reference_t<Iterator>>>`. 空范围将初值转换为结果类型返回；非空范围的首次调用接收初值，后续调用接收累积结果。

## 约束说明

迭代器与哨兵须形成有效范围，输出空间须足够。可调用对象、投影、写入或移动操作须满足对应算法的类型约束。接口不拥有输入或输出存储，不延长范围生命周期，也不提供设备线程间同步。 初值与结果须可移动，函数对象须可复制；初值须可转换为首个调用结果的去限定类型，后续调用结果须可赋给该结果。

## 调用示例

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[] = {1, 2, 3};
    auto result = asc::std::ranges::fold_left(values, 0, [](int total, int value) { return total * 10 + value; });
    return result == 123;
}
```

## 关联API

- [<asc/std/algorithm>](asc_std_algorithm.md)
