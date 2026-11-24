# asc::make_permutation_iterator

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

创建对应适配器，推导并按值保存所需状态。按索引访问随机访问数据，保持引用、代理和值的 const。

`<asc/iterator>`

## 声明

```cpp
namespace asc {
template <class I, class J>
constexpr permutation_iterator<I, J> make_permutation_iterator(I data_first, J index_current);
}  // namespace asc
```

## 约束说明

索引须非负、可表示且在范围内。允许重复索引读取，顺序重复写最后成功写入生效；重排要求独立目标，并发写入须避免冲突。位置比较使用索引位置。

最低 C++17，同时支持 C++20。函数按值保存并须可复制，借用对象在使用期间有效。比较和距离用于同一逻辑序列。构造和操作的 constexpr 及条件 noexcept 取决于实际步骤；下列原型省略内部约束参数和条件异常规格。

## 调用示例

```cpp
#include <asc/iterator>

bool example()
{
    int data[3] = {10, 20, 30};
    int indices[2] = {2, 0};
    auto it = asc::make_permutation_iterator(data, indices);
    it[1] = 7;
    return *it == 30 && data[0] == 7;
}
```

## 关联API

- [<asc/iterator>](asc_iterator.md)
