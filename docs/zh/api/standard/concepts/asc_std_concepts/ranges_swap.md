# asc::std::ranges::swap

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

头文件路径为：`<asc/std/concepts>`。

`asc::std::ranges::swap`是交换两个值的定制点对象：优先ADL发现的`swap`，其次等长数组逐元素交换，再次用`exchange`做移动交换。

标准语义参考：[cppreference `concepts`](https://en.cppreference.com/w/cpp/header/concepts)。

## 声明

swap是inline constexpr的定制点对象，实际实现类不作为公开接口。下列仅查询该对象的类型；swap_object_type是示例别名。调用形式为asc::std::ranges::swap(left, right)。

```cpp
using swap_object_type = decltype(asc::std::ranges::swap);
```

## 约束说明

- 优先使用ADL可找到的swap；参数是否可用及异常规格按该自定义调用判断。
- 其次支持等长数组逐元素交换；最后对可移动构造、可从右值赋值的同类型左值使用移动交换。
- 参与的对象须在整个调用期间有效；交换不会延长其生命周期，异常规格取决于被选中的实际操作。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/concepts>

bool example()
{
    int left = 1;
    int right = 2;
    asc::std::ranges::swap(left, right);
    int first[2] = {3, 4};
    int second[2] = {5, 6};
    asc::std::ranges::swap(first, second);
    return left == 2 && right == 1 && first[0] == 5 && second[1] == 4;
}
```

## 关联API

- [本头文件的接口列表](asc_std_concepts.md)
