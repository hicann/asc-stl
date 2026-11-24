# asc::make_transform_iterator

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

创建对应适配器，推导并按值保存所需状态。返回 const 函数对象作用于底层解引用结果的值或引用，保持返回值类别。

`<asc/iterator>`

## 声明

```cpp
namespace asc {
template <class I, class F>
constexpr transform_iterator<asc::std::decay_t<F>, I> make_transform_iterator(I current, F&& function);
}  // namespace asc
```

## 约束说明

读取结果须稳定，不消耗函数或输入状态。引用对象须保持有效。操作能力随底层；C++17 类别保持输入，C++20 按实际协议提供概念。

最低 C++17，同时支持 C++20。函数按值保存并须可复制，借用对象在使用期间有效。比较和距离用于同一逻辑序列。构造和操作的 constexpr 及条件 noexcept 取决于实际步骤；下列原型省略内部约束参数和条件异常规格。

## 调用示例

```cpp
#include <asc/iterator>

bool example()
{
    int data[2] = {3, 5};
    auto f = [](int x) { return x * 2; };
    auto it = asc::make_transform_iterator(data, f);
    return *it == 6 && it[1] == 10;
}
```

## 关联API

- [<asc/iterator>](asc_iterator.md)
