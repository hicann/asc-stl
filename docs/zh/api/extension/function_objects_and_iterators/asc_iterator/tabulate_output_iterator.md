# asc::tabulate_output_iterator

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

每次赋值调用一次 function(first+position,value)，回调返回值丢弃。

`<asc/iterator>`

## 声明

```cpp
namespace asc {
template <class Function, class Index = asc::std::ptrdiff_t, class Difference = asc::std::ptrdiff_t>
class tabulate_output_iterator;
}  // namespace asc
```

## 约束说明

索引与有符号差值分开。解引用和位置运算不调用回调；代理保存旧索引，函数副本可以有副作用，跨代理共享状态须显式捕获。

最低 C++17，同时支持 C++20。函数按值保存并须可复制，借用对象在使用期间有效。比较和距离用于同一逻辑序列。构造和操作的 constexpr 及条件 noexcept 取决于实际步骤；下列原型省略内部约束参数和条件异常规格。

## 调用示例

```cpp
#include <asc/iterator>

bool example()
{
    int data[2] = {};
    auto f = [&](asc::std::ptrdiff_t n, int x) { data[n] = x; };
    asc::tabulate_output_iterator<decltype(f)> it(f);
    *it++ = 3;
    *it = 5;
    return data[0] == 3 && data[1] == 5;
}
```

## 关联API

- [<asc/iterator>](asc_iterator.md)
