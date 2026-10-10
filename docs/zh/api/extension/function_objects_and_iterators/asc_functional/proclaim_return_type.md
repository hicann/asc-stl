# asc::proclaim_return_type

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

`asc::proclaim_return_type` 包装函数对象并显式声明其返回类型。

## 函数原型

```cpp
template<class R, class Function> constexpr asc::detail::return_type_wrapper<R, asc::std::decay_t<Function>> asc::proclaim_return_type(Function&& function) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `R` | 输入范围或视图的类型；须满足所选原型的遍历要求。 |
| `Function` | 对输入值执行本页操作的可调用对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `function` | 输入/输出 | 提供“包装函数对象并显式声明其返回类型”使用的对象引用；被引用对象须在调用期间有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::detail::return_type_wrapper<R, asc::std::decay_t<Function>>` | 返回类型。 |

## 约束说明

- 整数或逻辑运算仅在数学性质成立时报告对应特性
- 浮点加法不满足结合律

## 调用示例

以下片段给出具体模板实参和调用对象。

```cpp
#include <asc/functional>

decltype(auto) example()
{
    return asc::proclaim_return_type<int>([](int value) { return value + 1; });
}
```
