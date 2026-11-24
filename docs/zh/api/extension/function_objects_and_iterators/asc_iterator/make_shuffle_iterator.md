# asc::make_shuffle_iterator

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

创建对应适配器，推导并按值保存所需状态。每次读取调用一次确定的索引映射，位置移动不调用映射。

`<asc/iterator>`

## 声明

```cpp
namespace asc {
template <class D = asc::std::ptrdiff_t, class F, class Index = asc::std::size_t>
constexpr shuffle_iterator<Index, asc::std::decay_t<F>, D> make_shuffle_iterator(
    F&& mapping, Index first = 0, D position = 0);
}  // namespace asc
```

## 约束说明

映射是指定有限索引域上的双射，返回相同 Index 值类型。Index 与有符号 Difference 分开；这不是 Warp 交换或随机打乱算法。

最低 C++17，同时支持 C++20。函数按值保存并须可复制，借用对象在使用期间有效。比较和距离用于同一逻辑序列。构造和操作的 constexpr 及条件 noexcept 取决于实际步骤；下列原型省略内部约束参数和条件异常规格。

## 调用示例

```cpp
#include <asc/iterator>

bool example()
{
    auto mapping = [](asc::std::size_t n) { return asc::std::size_t{3} - n; };
    auto it = asc::make_shuffle_iterator(mapping);
    return *it == 3 && it[2] == 1;
}
```

## 关联API

- [<asc/iterator>](asc_iterator.md)
