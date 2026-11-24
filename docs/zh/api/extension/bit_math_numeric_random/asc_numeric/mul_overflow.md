# asc::mul_overflow

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

头文件路径为：`<asc/numeric>`。

计算同类型整数的精确积并检查是否可由T表示。

## 函数原型

```cpp
namespace asc {
template <class T>
[[nodiscard]] constexpr checked_result<T> mul_overflow(T left, T right) noexcept;
template <class T>
[[nodiscard]] constexpr bool mul_overflow(T left, T right, T& result) noexcept;
}  // namespace asc
```

## 参数说明

| 参数 | 类别 | 说明 |
| --- | --- | --- |
| `T` | 模板参数 | 共同的支持整数类型。 |
| `left` | 输入 | 左操作数，按值接收。 |
| `right` | 输入 | 右操作数，按值接收。 |
| `result` | 输出 | 仅输出引用形式提供；成功或失败均写回。 |

## 返回值说明

成功保存规定的数值并置failed为false；失败统一保存目标类型的零并置failed为true。输出引用形式总是写回，并以true返回失败；其数值和标志与对象形式一致。允许输出别名输入变量，运算使用写回前的值。函数为constexpr、noexcept并标注[[nodiscard]]，常量求值的失败也返回标志，不抛异常或终止。

## 约束说明

数学积超出T的可表示范围时失败。64位检查不要求设备提供更宽整数。

- `T`、`To`、`From`仅支持无cv的signed char、short、int、long、long long及五种无符号对应类型，数值位加符号位不超过64位。固定宽整数及size_t等别名按真实类型适用。
- bool、普通/宽/UTF字符、枚举、浮点、扩展整数和低精度包装不参与函数重载。非法checked_result<T>实例须编译诊断。
- 四则运算共同推导同一T；显式T时进入函数前的普通参数转换不属于检查范围，必要时先用overflow_cast检查原值。
- C++17和C++20采用同一契约；纯Host不依赖SDK。Device首批适用于支持相应标量整数运算的Ascend950PR/950DT CANN/BiSheng SIMT或普通SIMD标量代码。

## 调用示例

```cpp
#include <asc/numeric>
#include <asc/std/limits>

bool verify_example()
{
    const auto product = asc::mul_overflow(asc::std::numeric_limits<unsigned long long>::max(), 2ULL);
    int value = 3;
    const bool failed = asc::mul_overflow(value, value, value);
    return product.failed && product.value == 0ULL && !failed && value == 9;
}
```

## 关联API

- [<asc/numeric>](asc_numeric.md)
