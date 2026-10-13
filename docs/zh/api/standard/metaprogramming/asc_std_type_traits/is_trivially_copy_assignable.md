# asc::std::is_trivially_copy_assignable

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

`asc::std::is_trivially_copy_assignable` 在编译期判断给定操作是否能够平凡地可复制赋值。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

```cpp
template<class T> struct asc::std::is_trivially_copy_assignable
```

## 约束说明

- 提供特征类和 _v 辅助形式

## 调用示例

以下 Host 片段用具体类型实参和 `static_assert` 验证本页类型特征的结果。

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    struct custom_assign {
        custom_assign& operator=(const custom_assign&) { return *this; }
    };
    // 正例：int 的拷贝赋值是平凡的
    static_assert(asc::std::is_trivially_copy_assignable<int>::value);
    static_assert(asc::std::is_trivially_copy_assignable_v<int>);
    // 反例：用户提供拷贝赋值运算符的类拷贝赋值不是平凡的
    static_assert(!asc::std::is_trivially_copy_assignable_v<custom_assign>);
}
```
