# asc::std::alignment_of_v

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

头文件路径为：`<asc/std/type_traits>`。

`asc::std::alignment_of_v`在编译期取得类型的对齐要求，以size_t变量模板形式提供结果。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

以下声明摘要用公开特征类的`value`表示等价的常量值。

```cpp
namespace asc::std {
template<class T>
inline constexpr size_t alignment_of_v = alignment_of<T>::value;
} // namespace asc::std
```

## 约束说明

- `T`必须使`alignof(T)`合法，例如完整对象类型、引用到合法对象类型或元素类型完整的数组。不能使用`void`、函数或不完整类。
- 结果单位为字节，表示该类型对象的对齐要求；查询不分配内存。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/type_traits>

static_assert((asc::std::alignment_of_v<int>) == alignof(int));
```

## 关联API

- [本头文件的接口列表](asc_std_type_traits.md)
