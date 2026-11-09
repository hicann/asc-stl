# asc::std::ranges::sort

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

头文件路径为 `<asc/std/algorithm>`。按比较器与成员投影原地排序随机访问范围。接口以 C++17 起可调用的常量函数对象提供。

## 声明

以下给出已交付的调用形式；对象的实现类型不是接口承诺。省略的投影参数使用 `asc::std::identity`，排序默认使用 `asc::std::ranges::less`。

```cpp
namespace asc::std::ranges {
sort(first, last, compare = {}, projection = {});
}  // namespace asc::std::ranges
```

```cpp
namespace asc::std::ranges {
sort(range, compare = {}, projection = {});
}  // namespace asc::std::ranges
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入起始迭代器。 |
| `last` | 输入 | 输入结束哨兵。 |
| `compare` | 输入 | 满足严格弱序的比较器。 |
| `projection` | 输入 | 作用于输入元素的投影。 |
| `range` | 输入 | 要访问的范围；非拥有返回值受其生命周期约束。 |

## 返回值说明

`Iterator / borrowed_iterator_t<Range>`. 返回末迭代器；等价元素的相对顺序未指定。

## 约束说明

迭代器与哨兵须形成有效范围，输出空间须足够。可调用对象、投影、写入或移动操作须满足对应算法的类型约束。接口不拥有输入或输出存储，不延长范围生命周期，也不提供设备线程间同步。 非借用临时范围不返回可解引用的输入迭代器，而返回 `dangling`；借用范围的返回位置只能在底层存储有效期间使用。 需要可排序的随机访问迭代器。

## 调用示例

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[] = {3, 1, 4};
    auto result = asc::std::ranges::sort(values);
    return result == values + 3 && values[0] == 1 && values[1] == 3 && values[2] == 4;
}
```

## 关联API

- [<asc/std/algorithm>](asc_std_algorithm.md)
