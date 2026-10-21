# asc::std::literals::chrono_literals::operator""s

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

`operator"" s`以秒为单位构造时长；整数形式返回对应整数duration，浮点形式返回double计数的duration。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

位于asc::std::literals::chrono_literals命名空间。

```cpp
constexpr chrono::seconds operator"" s(unsigned long long value) noexcept;
```

```cpp
constexpr chrono::duration<double, ratio<1>> operator"" s(long double value) noexcept;
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 字面量的计数值，单位由后缀确定。整数形式须可由对应整数时长的rep表示；浮点形式转换为double计数，不先取整。 |

## 返回值说明

| 形式 | 返回值 |
| --- | --- |
| 整数 | 对应整数duration，计数取自value。 |
| 浮点 | duration<double, ratio<1>>，保留double可表示的分数计数。 |

## 约束说明

- 不同后缀分别表示小时、分钟、秒、毫秒、微秒和纳秒。
- 浮点输入转换到double时可能舍入；不保证保留long double的全部精度或范围。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/chrono>

bool example()
{
    constexpr auto value = asc::std::literals::chrono_literals::operator"" s(1.5L);
    return value.count() == 1.5;
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
