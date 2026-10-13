# asc::std::is_nothrow_invocable_r

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

`asc::std::is_nothrow_invocable_r` 在编译期判断调用及结果转换是否不抛出异常。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

```cpp
template<class Ret, class Fn, class ...Args> struct asc::std::is_nothrow_invocable_r
```

## 约束说明

- 提供特征类和 _v 辅助形式

## 调用示例

以下 Host 片段用具体类型实参和 `static_assert` 验证本页类型特征的结果。

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    using fn = int (*)(int);
    struct nothrow {
        int operator()(int) const noexcept { return 0; }
    };
    struct throws {
        int operator()(int) { throw 0; }
    };
    // 正例：noexcept 调用结果 int 可 noexcept 转换为 long
    static_assert(asc::std::is_nothrow_invocable_r<long, nothrow, int>::value);
    static_assert(asc::std::is_nothrow_invocable_r_v<long, nothrow, int>);
    // 反例：函数指针无法静态保证不抛出，operator() 可能抛出异常
    static_assert(!asc::std::is_nothrow_invocable_r_v<long, fn, int>);
    static_assert(!asc::std::is_nothrow_invocable_r_v<int, throws, int>);
}
```
