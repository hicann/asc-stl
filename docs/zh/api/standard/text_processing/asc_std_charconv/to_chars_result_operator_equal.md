# asc::std::to_chars_result::operator==

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

头文件路径为：`<asc/std/charconv>`。

`asc::std::to_chars_result::operator==` 逐成员比较两个转换结果：指针与错误码均相等时为 true。

标准语义参考：[cppreference `charconv`](https://en.cppreference.com/w/cpp/header/charconv)。

## 函数原型

```cpp
friend bool asc::std::to_chars_result::operator==(const to_chars_result&, const to_chars_result&) noexcept
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `to_chars_result` | 输出 | 接收接口结果的目标对象或存储；其容量和生命周期须满足约束说明。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 返回该操作产生的值，具体含义由所选原型确定。 |

## 约束说明

- 按指针与错误码双成员相等比较，恒不抛出

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/charconv>

template <class Object, class... Args>
decltype(auto) example(Object& object, Args&&... args)
{
    return object.operator==(static_cast<Args&&>(args)...);
}
```
