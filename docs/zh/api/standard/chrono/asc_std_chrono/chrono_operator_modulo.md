# asc::std::chrono::`operator%`

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

`asc::std::chrono::operator%`对时长计数求余，返回公共计时精度下的余数时长。

时长语义见[`duration`](chrono_duration.md)。

## 函数原型

通过`left % right`调用；隐藏友元通过实参相关查找参与，不能依赖限定命名空间查找。

### 原型1

所属类型：[`duration<Rep, Period>`](chrono_duration.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。声明摘要省略仅供重载选择的实现参数：`Rep2`不得为`duration`，且`const Rep2&`须能转换到`common_type_t<Rep, Rep2>`。

```cpp
template <class Rep2>
[[nodiscard]] friend constexpr duration<common_type_t<Rep, Rep2>, Period> operator%(const duration& left, const Rep2& right);
```

### 原型2

所属类型：[`duration<Rep, Period>`](chrono_duration.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
template <class Rep2, class Period2>
[[nodiscard]] friend constexpr common_type_t<duration, duration<Rep2, Period2>> operator%(const duration& left, const duration<Rep2, Period2>& right);
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rep2` | 另一操作数的计数或标量表示类型；与Rep形成公共计数类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 时长值；计数单位由其period决定，与另一时长运算时先形成公共计时周期。 |
| `right` | 输入 | 除数；须能转换到公共计数类型，取模时还须支持余数运算。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rep2` | 另一操作数的计数或标量表示类型；与Rep形成公共计数类型。 |
| `Period2` | 另一时长的tick周期，是以秒为基准的ratio类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 时长值；计数单位由其period决定，与另一时长运算时先形成公共计时周期。 |
| `right` | 输入 | 时长值；计数单位由其period决定，与另一时长运算时先形成公共计时周期。 |

## 返回值说明

| 适用原型 | 返回类型 | 含义 |
| --- | --- | --- |
| 原型1 | `duration<common_type_t<Rep, Rep2>, Period>` | 对公共计数做余数运算并返回duration；两个时长形式先换成公共周期。 |
| 原型2 | `common_type_t<duration, duration<Rep2, Period2>>` | 对公共计数做余数运算并返回duration；两个时长形式先换成公共周期。 |

## 约束说明

- 计数及中间运算须可表示。
- 对整型计数，当前实现把转换后为0的除数按1处理；这不是标准chrono的零除数保证。需要标准可移植语义时使用非零除数；有符号最小值除以-1不可表示时不得调用。
- 计数或公共计数类型须支持`%`；内建浮点计数不支持取模。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/chrono>

bool example()
{
    const asc::std::chrono::seconds value{7};
    return (value % 3).count() == 1 && (value % asc::std::chrono::seconds{3}).count() == 1;
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
