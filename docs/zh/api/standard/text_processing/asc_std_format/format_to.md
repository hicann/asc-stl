# asc::std::format_to

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

头文件路径为：`<asc/std/format>`。

`asc::std::format_to` 校验格式串并在调用方容量或结果大小约束内完成定长格式化。

该接口自 C++20+ 模式起提供。

标准语义参考：[cppreference `format`](https://en.cppreference.com/w/cpp/header/format)。

## 函数原型

```cpp
template<class ...Args> char* asc::std::format_to(char* output, format_string<Args...> format, Args&&... args);
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Args` | 传递给构造函数或可调用对象的实参类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `output` | 输出 | 提供“校验格式串并在调用方容量或结果大小约束内完成定长格式化”所需的数据地址；可访问范围和生命周期须满足约束。 |
| `format` | 输入 | 转发给对象构造或函数调用的实参列表。 |
| `args` | 输入/输出 | 转发给对象构造或函数调用的实参列表。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `char *` | 返回格式化输出结束位置；`format_to_n` 还报告完整结果所需字符数。 |

## 约束说明

- format_to、format_to_n、formatted_size的调用方固定char*输出子集
- bool/char/C字符串默认{}，非bool/char标准整数的{}及d/x/X/o/b
- 转义花括号、截断、负n、总长度和允许未使用尾部参数
- 不分配
- Host、AI Core SIMD 编程 和 AI Core SIMT 编程

## 调用示例

以下 Host 片段展示固定缓冲或多维视图的具体调用；底层存储须保持有效。

```cpp
#include <asc/std/format>

decltype(auto) example()
{
    char output[32] = {};
    return asc::std::format_to(output, "{}", 7);
}
```
