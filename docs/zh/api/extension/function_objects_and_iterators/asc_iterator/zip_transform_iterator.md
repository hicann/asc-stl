# asc::zip_transform_iterator

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

组合别名 transform_iterator<zip_function<F>,zip_iterator<I...>>，同时读取并展开各分量给函数。

`<asc/iterator>`

## 声明

```cpp
namespace asc {
template <class Function, class... Iterators>
using zip_transform_iterator = transform_iterator<zip_function<Function>, zip_iterator<Iterators...>>;
}  // namespace asc
```

## 约束说明

全部分量可读，复用组合位置、终点、移动和返回规则。返回引用不能指向临时组合代理中的按值分量。

最低 C++17，同时支持 C++20。函数按值保存并须可复制，借用对象在使用期间有效。比较和距离用于同一逻辑序列。构造和操作的 constexpr 及条件 noexcept 取决于实际步骤；下列原型省略内部约束参数和条件异常规格。

## 调用示例

```cpp
#include <asc/iterator>

bool example()
{
    int a[2] = {1, 2}, b[2] = {10, 20};
    auto f = [](int x, int y) { return x + y; };
    asc::zip_transform_iterator<decltype(f), int*, int*> it(asc::make_zip_iterator(a, b), asc::make_zip_function(f));
    return *it == 11 && it[1] == 22;
}
```

## 关联API

- [<asc/iterator>](asc_iterator.md)
