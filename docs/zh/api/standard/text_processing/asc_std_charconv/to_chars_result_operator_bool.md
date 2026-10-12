# asc::std::to_chars_result::operator bool

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

`asc::std::to_chars_result::operator bool` 返回转换是否无错误发生：`ec == errc{}` 时为 true，支持条件判断惯用法。

标准语义参考：[cppreference `charconv`](https://en.cppreference.com/w/cpp/header/charconv)。

## 函数原型

```cpp
explicit asc::std::to_chars_result::operator bool() const noexcept
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `explicit` | 返回该操作产生的值，具体含义由所选原型确定。 |

## 约束说明

- 结果为 true 当且仅当错误码等于默认构造的 errc

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/charconv>

template <class Object, class... Args>
decltype(auto) example(Object& object, Args&&... args)
{
    return object.operator bool(static_cast<Args&&>(args)...);
}
```
