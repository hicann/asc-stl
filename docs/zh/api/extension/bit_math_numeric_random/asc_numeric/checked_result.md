# asc::checked_result

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

聚合类型checked_result<T>保存数值及失败标志。

## 声明

```cpp
namespace asc {
template <class T>
struct checked_result {
    T value{};
    bool failed{};
};
}  // namespace asc
```

## 约束说明

value和failed为仅有的公开数据成员，分别默认初始化为零和false；默认初始化和值初始化一致。支持结构化绑定、标准布局和平凡复制，不提供布尔转换。

- `T`、`To`、`From`仅支持无cv的signed char、short、int、long、long long及五种无符号对应类型，数值位加符号位不超过64位。固定宽整数及size_t等别名按真实类型适用。
- bool、普通/宽/UTF字符、枚举、浮点、扩展整数和低精度包装不参与函数重载。非法checked_result<T>实例须编译诊断。
- 四则运算共同推导同一T；显式T时进入函数前的普通参数转换不属于检查范围，必要时先用overflow_cast检查原值。
- C++17和C++20采用同一契约；纯Host不依赖SDK。Device首批适用于支持相应标量整数运算的Ascend950PR/950DT CANN/BiSheng SIMT或普通SIMD标量代码。

## 调用示例

```cpp
#include <asc/numeric>

bool verify_example()
{
    const asc::checked_result<int> defaulted;
    const auto [value, failed] = asc::add_overflow(2, 3);
    return defaulted.value == 0 && !defaulted.failed && value == 5 && !failed;
}
```

## 关联API

- [<asc/numeric>](asc_numeric.md)
