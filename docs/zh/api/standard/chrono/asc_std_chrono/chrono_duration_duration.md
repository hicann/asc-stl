# asc::std::chrono::duration::duration

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

`asc::std::chrono::duration::duration`按本页所列构造形态初始化`duration`对象。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

### 原型1

```cpp
constexpr duration();
```

### 原型2

```cpp
template<class Rep2, class Period2> constexpr duration(const duration<Rep2, Period2>& count);
```

### 原型3

```cpp
template<class Rep2> explicit constexpr duration(const Rep2& count);
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rep2` | 来源计数的表示类型，须满足目标duration的转换条件。 |
| `Period2` | 来源duration的计时单位，以ratio表示。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `count` | 输入 | 来源时长；计数单位由其Period2决定，按目标Period换算后初始化。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rep2` | 来源计数的表示类型，须满足目标duration的转换条件。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `count` | 输入 | 初始化计数值；一个tick表示Period::num / Period::den秒。 |

## 返回值说明

无返回值。

## 约束说明

- 提供值运算以及六个显式关系运算符。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::duration<int> value{7};
    return value.count() == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
