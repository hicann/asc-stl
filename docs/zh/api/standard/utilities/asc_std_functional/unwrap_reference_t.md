# asc::std::unwrap_reference_t

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

头文件路径为：`<asc/std/functional>`。

`asc::std::unwrap_reference_t`取得引用包装器保存的引用类型或按规则退化后的类型。

标准语义参考：[cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional)。

## 声明

```cpp
namespace asc::std {
template<class T> using unwrap_reference_t = typename unwrap_reference<T>::type;
} // namespace asc::std
```

## 约束说明

- 支持标准可调用对象和成员指针形式。

## 调用示例

以下片段选用具体模板实参展示别名类型。

```cpp
#include <asc/std/functional>

void use_type()
{
    using selected = asc::std::unwrap_reference_t<int>;
}
```

## 关联API

- [本头文件的接口列表](asc_std_functional.md)
