# asc::make_discard_iterator

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

创建对应适配器，推导并按值保存所需状态。丢弃赋值，不读取、移动或转换实参；右侧表达式仍正常求值。

`<asc/iterator>`

## 声明

```cpp
namespace asc {
constexpr discard_iterator make_discard_iterator(asc::std::ptrdiff_t position = 0) noexcept;
}  // namespace asc
```

## 约束说明

默认位置0有效，位置类型为有符号 ptrdiff_t。输出协议和额外位置算术不使其成为可读迭代器。

最低 C++17，同时支持 C++20。函数按值保存并须可复制，借用对象在使用期间有效。比较和距离用于同一逻辑序列。构造和操作的 constexpr 及条件 noexcept 取决于实际步骤；下列原型省略内部约束参数和条件异常规格。

## 调用示例

```cpp
#include <asc/iterator>

bool example()
{
    int evaluated = 0;
    auto it = asc::make_discard_iterator();
    *it++ = ++evaluated;
    return evaluated == 1 && it.index() == 1;
}
```

## 关联API

- [<asc/iterator>](asc_iterator.md)
