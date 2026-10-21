# asc::std::underlying_type_t

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

`asc::std::underlying_type_t`把对应类型特征的`type`成员直接暴露为类型别名。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

```cpp
namespace asc::std {
template<class T> using underlying_type_t = typename underlying_type<T>::type;
} // namespace asc::std
```

## 约束说明

- `T`须为枚举类型，且其底层整数类型必须已经确定。
- 对非枚举类型，不能假定存在结果成员`type`；在模板中使用时应先检查枚举条件或通过替换失败约束参与。

## 调用示例

以下Host示例使用独立的预期类型或值检查接口结果。

```cpp
#include <asc/std/type_traits>

enum class sample_enum : unsigned char { value };
using result_type = asc::std::underlying_type_t<sample_enum>;
static_assert(asc::std::is_same_v<result_type, unsigned char>);
```

## 关联API

- [本头文件的接口列表](asc_std_type_traits.md)
