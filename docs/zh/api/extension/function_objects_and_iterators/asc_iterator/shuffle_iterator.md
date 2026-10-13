# asc::shuffle_iterator

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

`asc::shuffle_iterator`按确定性映射重排索引后访问底层随机访问迭代器。

## 声明

```cpp
namespace asc {
template<class Index, class Bijection> class shuffle_iterator;
} // namespace asc
```

## 约束说明

- 提供惰性、非拥有的迭代器适配器及其工厂。
- 操作数必须在当前执行位置有效。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/iterator>

int reverse_three(int index) { return 2 - index; }

bool example()
{
    asc::shuffle_iterator<int, int(*)(int)> iterator(reverse_three, 0);
    const bool first = *iterator == 2;
    ++iterator;
    return first && *iterator == 1;
}
```

## 关联API

- [本头文件的接口列表](asc_iterator.md)
