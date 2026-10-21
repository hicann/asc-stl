# asc::always_false::`operator()`

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

`asc::always_false::operator()`忽略全部参数并返回false。

## 函数原型

所属类型：[`asc::always_false`](always_false.md)。

```cpp
// asc::always_false 类内的声明节选；模板形参和其他成员由所属类提供。
template <class... Args>
constexpr bool operator()(Args&&...) const noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Args` | 传递给构造函数或可调用对象的实参类型列表。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 本页对象只执行所述谓词、比较或编译期属性查询，不进行Runtime提交。
- 比较操作数须支持相应运算；透明min/max可能返回引用，选中对象须在使用期间有效。
- 复制参数声明只表明调用方的复制承诺，不延长捕获引用的生命周期，也不代替可调用性检查。

## 调用示例

以下Host片段以具体值演示调用；输入须满足本页约束。

```cpp
#include <asc/functional>

decltype(auto) example()
{
    return asc::always_false{}(7);
}
```

## 关联API

- [`asc::always_false`](always_false.md)
- [本头文件的接口列表](asc_functional.md)
