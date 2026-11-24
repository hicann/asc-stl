# asc::constant_iterator

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

按值拥有可复制的常量，每次解引用返回 T 值，不暴露迭代器内部引用。

`<asc/iterator>`

## 声明

```cpp
namespace asc {
template <class T, class Difference = asc::std::ptrdiff_t>
class constant_iterator;
}  // namespace asc
```

## 约束说明

T 是完整、无顶层 cv 的非数组对象；Difference 必须有符号。C++17 类别为输入，C++20 可满足随机访问概念。

最低 C++17，同时支持 C++20。函数按值保存并须可复制，借用对象在使用期间有效。比较和距离用于同一逻辑序列。构造和操作的 constexpr 及条件 noexcept 取决于实际步骤；下列原型省略内部约束参数和条件异常规格。

## 调用示例

```cpp
#include <asc/iterator>

bool example()
{
    asc::constant_iterator<int> it(7);
    it += 2;
    return it[1] == 7 && it.index() == 2;
}
```

## 关联API

- [<asc/iterator>](asc_iterator.md)
