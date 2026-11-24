# asc::overflow_cast

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

检查原整数值能否由目标类型To表示，并在成功时保持其数值。

## 函数原型

```cpp
namespace asc {
template <class To, class From>
[[nodiscard]] constexpr checked_result<To> overflow_cast(From value) noexcept;
}  // namespace asc
```

## 参数说明

| 参数 | 类别 | 说明 |
| --- | --- | --- |
| `To` | 模板参数 | 目标整数类型。 |
| `From` | 模板参数 | 由实参推导的源整数类型。 |
| `value` | 输入 | 待检查的原整数值。 |

## 返回值说明

成功保存规定的数值并置failed为false；失败统一保存目标类型的零并置failed为true。输出引用形式总是写回，并以true返回失败；其数值和标志与对象形式一致。允许输出别名输入变量，运算使用写回前的值。函数为constexpr、noexcept并标注[[nodiscard]]，常量求值的失败也返回标志，不抛异常或终止。

## 约束说明

按原值与To的最小/最大值判断可表示性；负数转无符号类型失败。不能以转换后的往返相等代替检查。

- `T`、`To`、`From`仅支持无cv的signed char、short、int、long、long long及五种无符号对应类型，数值位加符号位不超过64位。固定宽整数及size_t等别名按真实类型适用。
- bool、普通/宽/UTF字符、枚举、浮点、扩展整数和低精度包装不参与函数重载。非法checked_result<T>实例须编译诊断。
- 四则运算共同推导同一T；显式T时进入函数前的普通参数转换不属于检查范围，必要时先用overflow_cast检查原值。
- C++17和C++20采用同一契约；纯Host不依赖SDK。Device首批适用于支持相应标量整数运算的Ascend950PR/950DT CANN/BiSheng SIMT或普通SIMD标量代码。

## 调用示例

```cpp
#include <asc/numeric>

bool verify_example()
{
    const auto valid = asc::overflow_cast<unsigned char>(42);
    const auto invalid = asc::overflow_cast<unsigned>(-1);
    return !valid.failed && valid.value == 42 && invalid.failed && invalid.value == 0;
}
```

## 关联API

- [<asc/numeric>](asc_numeric.md)
