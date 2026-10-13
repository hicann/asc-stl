# asc::strided_iterator

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

头文件路径为：`<asc/iterator>`。

`asc::strided_iterator`是借用底层随机访问迭代器的定步长适配器。支持正、负非零步长的完整随机访问操作，包括双向移动、下标、顺序比较、迭代器距离及标准迭代器traits；单次移动对应底层移动一个步长。

## 声明

```cpp
namespace asc {
template<class Iterator, class Stride = asc::std::ptrdiff_t> class strided_iterator;
} // namespace asc
```

## 约束说明

- 步长必须非零。
- 参与距离或顺序比较的迭代器须使用相同步长，底层位置须按步长对齐。
- 迭代器及其底层范围在使用期间必须有效。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/iterator>

bool example()
{
    int values[4] = {1, 2, 3, 4};
    asc::strided_iterator<int*> iterator(values, 2);
    const bool first = *iterator == 1;
    ++iterator;
    return first && *iterator == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_iterator.md)
