# asc::std::reference_wrapper::`operator()`

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

`asc::std::reference_wrapper::operator()`按`reference_wrapper`的可用运算符规则处理当前对象及操作数。

标准语义参考：[cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional)。

## 函数原型

所属类型：[`asc::std::reference_wrapper`](reference_wrapper.md)。

```cpp
// asc::std::reference_wrapper 类内的声明节选；模板形参和其他成员由所属类提供。
template<class ...ArgTypes> constexpr invoke_result_t<type&, ArgTypes...> operator()(ArgTypes&&... args) const noexcept(is_nothrow_invocable_v<T&, ArgTypes...>);
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ArgTypes` | 转发给被包装可调用对象的实参类型列表。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `invoke_result_t<type &, ArgTypes...>` | 返回函数对象按所选实参调用得到的结果。 |

## 约束说明

- 支持标准可调用对象和成员指针形式。

## 调用示例

以下Host片段使用具体类型演示调用；输入范围和对象须在使用期间有效。

```cpp
#include <asc/std/functional>

struct function_object { int operator()(int value) const { return value + 1; } };

decltype(auto) example(function_object& function)
{
    asc::std::reference_wrapper<function_object> reference(function);
    return reference(7);
}

bool verify_example()
{
    function_object function;
    return example(function) == 8;
}
```

## 关联API

- [`asc::std::reference_wrapper`](reference_wrapper.md)
- [本头文件的接口列表](asc_std_functional.md)
