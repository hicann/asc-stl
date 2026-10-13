# asc::std::chrono::is_am

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

头文件路径为：`<asc/std/chrono>`。

`asc::std::chrono::is_am` 判断小时值是否位于上午范围。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

```cpp
[[nodiscard]] constexpr bool asc::std::chrono::is_am(const hours& value) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 以 24 小时制表示的小时（hours），取值 0 到 23；处于 0 到 11（上午）时返回 true。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回 `true`，否则返回 `false`。 |

## 约束说明

- 纯日历/组合/别名/字面量为Host、AI Core SIMD 编程 和 AI Core SIMT 编程
- system_clock仅为sys_time精确形状提供类型、rep/period/duration/time_point和is_steady类型

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/chrono>

decltype(auto) example(const asc::std::chrono::hours & value)
{
    return asc::std::chrono::is_am(value);
}
```
