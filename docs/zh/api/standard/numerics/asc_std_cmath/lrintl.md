# asc::std::lrintl

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

`asc::std::lrintl`由`<asc/std/cmath>`提供，宿主long double按舍入模式取整转long，后缀l别名

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

各重载自C++17起提供。执行位置限定按下列原型分别说明；执行位置宏已省略。

### 原型1

```cpp
namespace asc::std {
[[nodiscard]] constexpr long lrintl(long double value) noexcept;
}
```

可用位置：Host。long double相关重载要求Host启用该类型支持。

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按当前舍入模式取整并转换为long的输入值（无量纲）。 |

## 返回值说明

返回类型按各原型确定（`long`）。按当前舍入方向转换为long。

## 约束说明

- 输入为NaN、无穷或舍入结果超出返回整数类型可表示范围时，没有可移植的数值结果；具体值及浮点异常由Host或Device后端决定，不应依赖固定整数哨兵。

- 宿主long double按舍入模式取整转long，后缀l别名。

## 调用示例

以下Host示例给出具体输入和预期结果。

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::lrintl(2.0L);
    return result == 2L;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
