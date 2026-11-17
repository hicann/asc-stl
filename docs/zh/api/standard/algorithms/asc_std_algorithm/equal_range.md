# asc::std::equal_range

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

头文件路径为：`<asc/std/algorithm>`。

`asc::std::equal_range`在已排序范围中返回与目标等价的半开子区间；在调用者所在执行主体内顺序执行。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template <class ForwardIterator, class T, class Compare>
[[nodiscard]] constexpr pair<ForwardIterator, ForwardIterator> equal_range(
    ForwardIterator first, ForwardIterator last, const T& value, Compare compare);
}  // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template <class ForwardIterator, class T>
[[nodiscard]] constexpr pair<ForwardIterator, ForwardIterator> equal_range(
    ForwardIterator first, ForwardIterator last, const T& value);
}  // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ForwardIterator` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `T` | 待查找值的类型，须能作为compare的实参与元素比较。 |
| `Compare` | 比较器类型；调用形式为compare(a, b)，返回bool且满足严格弱序。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 已排序输入范围的起始迭代器或指针。 |
| `last` | 输入 | 已排序输入范围的结束位置，不包含该位置。 |
| `value` | 输入 | 待查找的值；返回范围内与该值等价元素构成的子范围边界。 |
| `compare` | 输入 | 比较器，按调用形式compare(a, b)返回bool，true表示a排在b前；须满足严格弱序，与范围排序规则一致。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ForwardIterator` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `T` | 输入范围元素或参与运算的值类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 已排序输入范围的起始迭代器或指针。 |
| `last` | 输入 | 已排序输入范围的结束位置，不包含该位置。 |
| `value` | 输入 | 待查找的值；返回范围内与该值等价元素构成的子范围边界。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `pair<ForwardIterator, ForwardIterator>` | 返回与目标值等价的半开子区间。 |
| 原型2 | `pair<ForwardIterator, ForwardIterator>` | 返回与目标值等价的半开子区间。 |

等价由 `!compare(element, value) && !compare(value, element)` 定义，不要求
`element == value`。没有等价元素时，两个迭代器都指向插入位置，该位置可能位于输入范围内部。
输入为空时，两者都是 `first`。对于随机访问迭代器，两个返回迭代器之差就是候选数量，
无需逐个扫描等价元素。

## 约束说明

- 提供顺序执行且不进行动态内存分配的重载。

## 调用示例

以下 Host 示例在按键排序的表中为一批查询定位候选行。每个返回区间包含全部匹配行，
包括重复键；未命中的键在其插入位置得到零个候选。SIMT 算子可以让每个线程处理一个查询，
`equal_range` 本身仍在线程内部顺序执行。

```cpp
#include <asc/std/algorithm>

bool example()
{
    int row_keys[6] = {2, 2, 2, 5, 5, 9};
    int queries[4] = {2, 4, 9, 10};
    int begins[4] = {}, ends[4] = {}, counts[4] = {};
    for (int i = 0; i < 4; ++i) {
        const auto rows = asc::std::equal_range(row_keys, row_keys + 6, queries[i]);
        begins[i] = static_cast<int>(rows.first - row_keys);
        ends[i] = static_cast<int>(rows.second - row_keys);
        counts[i] = ends[i] - begins[i];
    }
    return begins[0] == 0 && ends[0] == 3 && counts[0] == 3 &&
        begins[1] == 3 && ends[1] == 3 && counts[1] == 0 &&
        begins[2] == 5 && ends[2] == 6 && counts[2] == 1 &&
        begins[3] == 6 && ends[3] == 6 && counts[3] == 0;
}
```

## 关联API

- [本头文件的接口列表](asc_std_algorithm.md)
