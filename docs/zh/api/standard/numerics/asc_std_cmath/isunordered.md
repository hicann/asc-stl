# asc::std::isunordered

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

`asc::std::isunordered`按名称指定的浮点比较关系判断输入值，并遵守NaN的无序规则。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

各重载自C++17起提供。执行位置限定按下列原型分别说明；执行位置宏已省略。

### 原型1

```cpp
namespace asc::std {
[[nodiscard]] bool isunordered(float x, float y) noexcept;
}
```

可用位置：Host、AI Core SIMT编程。

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `x` | 输入 | 参与x与y是否无序 比较的左操作数（无量纲）；任一操作数为NaN时结果为true且不触发浮点异常。 |
| `y` | 输入 | 参与x与y是否无序 比较的右操作数（无量纲）。 |

## 返回值说明

返回类型按各原型确定（`bool`）。至少一个输入为NaN时返回true。

## 约束说明

- 提供float函数重载、求值类型别名、比较函数、nanf和分类宏。

## 调用示例

以下Host示例给出具体输入和预期结果。

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::isunordered(1.0F, 2.0F);
    return result == false;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
