# asc::make_zip_function

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

创建对应适配器，推导并按值保存所需状态。保存函数，将标准层 tuple、pair、array 或 zip 代理中的各项展开为参数。

`<asc/iterator>`

## 声明

```cpp
namespace asc {
template <class F>
constexpr zip_function<asc::std::decay_t<F>> make_zip_function(F&& function);
}  // namespace asc
```

## 约束说明

四种 cv/ref 调用保持函数和元素的值类别并返回 decltype(auto)。作为读迭代器的函数时，另须可复制、const 可调用且结果稳定。

最低 C++17，同时支持 C++20。函数按值保存并须可复制，借用对象在使用期间有效。比较和距离用于同一逻辑序列。构造和操作的 constexpr 及条件 noexcept 取决于实际步骤；下列原型省略内部约束参数和条件异常规格。

## 调用示例

```cpp
#include <asc/iterator>

bool example()
{
    auto f = [](int a, int b) { return a + b; };
    auto it = asc::make_zip_function(f);
    return it(asc::std::tuple<int, int>{3, 7}) == 10;
}
```

## 关联API

- [<asc/iterator>](asc_iterator.md)
