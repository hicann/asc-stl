# asc::proclaims_copyable_arguments

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

头文件路径为：`<asc/functional>`。

`asc::proclaims_copyable_arguments`判断函数对象是否显式声明其参数可按值复制后调用。

## 声明

```cpp
namespace asc {
template <class Function, class... Args>
struct proclaims_copyable_arguments;
}  // namespace asc
```

## 约束说明

- 本页对象只执行所述谓词、比较或编译期属性查询，不进行Runtime提交。
- 比较操作数须支持相应运算；透明min/max可能返回引用，选中对象须在使用期间有效。
- 复制参数声明只表明调用方的复制承诺，不延长捕获引用的生命周期，也不代替可调用性检查。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/functional>

bool example()
{
    static_assert(asc::proclaims_copyable_arguments<asc::always_true>::value);
    static_assert(!asc::proclaims_copyable_arguments<int>::value);
    return asc::always_true{}(7) && !asc::always_false{}(7);
}
```

## 关联API

- [本头文件的接口列表](asc_functional.md)
