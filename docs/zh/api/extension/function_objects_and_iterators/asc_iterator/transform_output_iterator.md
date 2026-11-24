# asc::transform_output_iterator

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

解引用生成保存位置和函数副本的只写代理；赋值时转发实参，调用一次函数并写入一次。

`<asc/iterator>`

## 声明

```cpp
namespace asc {
template <class Function, class Iterator>
class transform_output_iterator;
}  // namespace asc
```

## 约束说明

const 目标不可写。const 代理可赋值，临时适配器销毁后仍可在底层目标和捕获对象有效时使用。后置操作保留旧目标，支持 *it++ = value；输出函数副本允许副作用。

最低 C++17，同时支持 C++20。函数按值保存并须可复制，借用对象在使用期间有效。比较和距离用于同一逻辑序列。构造和操作的 constexpr 及条件 noexcept 取决于实际步骤；下列原型省略内部约束参数和条件异常规格。

## 调用示例

```cpp
#include <asc/iterator>

bool example()
{
    int data[2] = {};
    auto f = [](int x) { return x * 2; };
    asc::transform_output_iterator<decltype(f), int*> it(data, f);
    *it++ = 3;
    *it = 4;
    return data[0] == 6 && data[1] == 8;
}
```

## 关联API

- [<asc/iterator>](asc_iterator.md)
