# asc::std::make_unsigned_t

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

`asc::std::make_unsigned_t`产生保持宽度规则并调整整数符号性的类型，以类型别名形式提供结果。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

以下用公开特征类表示本别名的等价类型，不依赖内部实现辅助名字。

```cpp
namespace asc::std {
template<class T>
using make_unsigned_t = typename make_unsigned<T>::type;
} // namespace asc::std
```

## 约束说明

- 提供特征类以及标准的 _t、_v辅助形式。

## 调用示例

以下Host示例使用独立的预期类型或值检查接口结果。

```cpp
#include <asc/std/type_traits>

using result_type = asc::std::make_unsigned_t<int>;
static_assert(asc::std::is_same_v<result_type, unsigned int>);
```

## 关联API

- [本头文件的接口列表](asc_std_type_traits.md)
