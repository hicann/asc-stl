# asc::std::nanf

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

头文件路径为：`<asc/std/cmath>`。

`asc::std::nanf`构造静默NaN值；Device侧适用范围以本页float与执行位置约束为准。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

```cpp
namespace asc::std {
float nanf(const char* tag) noexcept;
} // namespace asc::std
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tag` | 输入 | 生成静默NaN所用的负载标记（以空字符结尾的字符串）；其内容映射到返回NaN的尾数位，空串表示无特定负载。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `float` | 返回静默NaN值；Device侧适用范围以本页float与执行位置约束为准。 |

## 约束说明

- 提供float函数重载、求值类型别名、比较函数、nanf和分类宏。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cmath>

decltype(auto) example(const char * tag)
{
    return asc::std::nanf(tag);
}
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
