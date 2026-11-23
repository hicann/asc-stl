# asc::equal_to_value::equal_to_value

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

头文件：`<asc/functional>`。转发实参，直接构造保存值。

## 声明

```cpp
// Inside equal_to_value<T>; declaration constraints are omitted.
template<class U>
explicit constexpr equal_to_value(U&& value)
    noexcept(asc::std::is_nothrow_constructible_v<T, U&&>);

// Deduction guide; existing equal_to_value specializations are excluded.
template<class U>
equal_to_value(U&&) -> equal_to_value<asc::std::decay_t<U>>;
```

## 约束说明

无默认构造。构造要求T可从U&&构造；转发构造不抢占本类型的复制/移动构造，复制推导保持已有谓词类型。所需操作允许时可常量求值。

C++17和C++20均支持。Host、SIMT、SIMD标量调用须满足当前调用域的比较、转换、构造和析构要求；Device调用遵守无异常执行约定。

## 调用示例

```cpp
#include <asc/functional>

bool example()
{
    int target = 7;
    const auto equal = asc::equal_to_value{target};
    target = 9;
    return equal(7) && !equal(target);
}
```

## 关联API

- [本头文件的接口列表与运算支持表](asc_functional.md)
