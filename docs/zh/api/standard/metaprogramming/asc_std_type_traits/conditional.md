# asc::std::conditional

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

`conditional<B, T, U>`按编译期布尔值在两个类型之间选择。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

### 主模板声明

```cpp
namespace asc::std {
template<bool B, class If, class Then> struct conditional;
} // namespace asc::std
```

### 偏特化声明

```cpp
namespace asc::std {
template<class If, class Then> struct conditional<false, If, Then>;
} // namespace asc::std
```

## 约束说明

- `B`为编译期布尔条件；为`true`时成员类型`type`为`If`，为`false`时为`Then`。
- 偏特化为主模板在`B == false`时提供另一种定义，不是第二个函数重载。

## 调用示例

以下Host片段用具体类型实参和`static_assert`验证本页类型特征的结果。

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    // 条件为真选第一实参，为假选第二实参
    static_assert(asc::std::is_same_v<asc::std::conditional<true, int, long>::type, int>);
    static_assert(asc::std::is_same_v<asc::std::conditional_t<false, int, long>, long>);
    // 反例：真条件不会选择第二实参
    static_assert(!asc::std::is_same_v<asc::std::conditional_t<true, int, long>, long>);
}
```

## 关联API

- [本头文件的接口列表](asc_std_type_traits.md)
