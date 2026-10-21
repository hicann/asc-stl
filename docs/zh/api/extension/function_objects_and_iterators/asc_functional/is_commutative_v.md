# asc::is_commutative_v

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

头文件路径为：`<asc/functional>`。

`asc::is_commutative_v`表示指定运算在该类型上是否满足交换律。

## 声明

```cpp
namespace asc {
template <class Operator, class T>
inline constexpr bool is_commutative_v = asc::is_associative_v<Operator, T>;
}  // namespace asc
```

## 约束说明

- 声明代码展示主模板；bool逻辑组合与满足全序值域的minimum<T>/maximum<T>另有为true的特化。

- 标准运算仅登记匹配的`Operator<T>`／`T`组合或透明`Operator<void>`；不匹配的值类型返回false。
- 整数加法单位元为0，乘法单位元为1、吸收元为0；逻辑运算只登记bool；位运算只登记无符号整数。
- 算术结合律登记无符号类型；乘法进一步限unsigned int、unsigned long、unsigned long long，避免窄整数提升后发生有符号溢出。浮点加法／乘法不作此登记。
- minimum／maximum的已有登记要求调用方使用满足全序的值域；NaN和非全序自定义比较不能据此认定重新分组安全。

## 调用示例

以下片段用具体模板实参读取接口值。

```cpp
#include <asc/functional>

inline constexpr auto example = asc::is_commutative_v<asc::minimum<int>, int>;
```

## 关联API

- [本头文件的接口列表](asc_functional.md)
