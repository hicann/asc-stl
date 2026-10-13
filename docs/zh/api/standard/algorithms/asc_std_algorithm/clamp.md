# asc::std::clamp

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

头文件路径为：`<asc/std/algorithm>`。

`asc::std::clamp`用于将`value`限制在由`lower`和`upper`确定的闭区间内，自C++17起提供。当`value`位于下界之前时返回`lower`，位于上界之后时返回`upper`，否则返回`value`；需要使用自定义顺序时，可通过`compare`参数指定比较规则。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<class T, class Compare> [[nodiscard]] constexpr const T& clamp(const T& value, const T& lower, const T& upper, Compare compare);
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<class T> [[nodiscard]] constexpr const T& clamp(const T& value, const T& lower, const T& upper);
} // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | value、lower和upper的类型；三个参数必须能够按照所选比较规则进行比较。 |
| `Compare` | 自定义比较对象的类型；该对象用于判断第一个参数是否位于第二个参数之前。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待限制到指定区间内的值。 |
| `lower` | 输入 | 区间下界。 |
| `upper` | 输入 | 区间上界。 |
| `compare` | 输入 | 自定义比较对象；compare(left, right)返回true时表示left位于right之前。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | value、lower和upper的类型；三个参数必须能够按照所选比较规则进行比较。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待限制到指定区间内的值。 |
| `lower` | 输入 | 区间下界。 |
| `upper` | 输入 | 区间上界。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `const T &` | 返回value、lower或upper中一个对象的常量引用；被引用对象在结果使用期间必须保持有效。 |
| 原型2 | `const T &` | 返回value、lower或upper中一个对象的常量引用；被引用对象在结果使用期间必须保持有效。 |

## 约束说明

- lower和upper必须按所选比较关系构成有效区间。
- compare必须建立严格弱序且不能修改参与比较的对象。
- 返回引用不延长value、lower或upper的生命周期。

## 调用示例

以下示例分别处理小于下界、位于区间内和大于上界的输入，并检查返回值及其引用的对象。

```cpp
#include <asc/std/algorithm>

bool example()
{
    const int lower = 0;
    const int upper = 10;
    const int below = -3;
    const int middle = 4;
    const int above = 12;

    const int& lower_result = asc::std::clamp(below, lower, upper);
    const int& middle_result = asc::std::clamp(middle, lower, upper);
    const int& upper_result = asc::std::clamp(above, lower, upper);

    // 小于下界时引用 lower；位于区间内时引用原值；
    // 大于上界时引用 upper。
    return lower_result == 0 && &lower_result == &lower
        && middle_result == 4 && &middle_result == &middle
        && upper_result == 10 && &upper_result == &upper;
}
```

## 关联API

- [本头文件的接口列表](asc_std_algorithm.md)
