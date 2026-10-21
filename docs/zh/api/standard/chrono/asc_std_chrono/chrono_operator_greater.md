# asc::std::chrono::`operator>`

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

`asc::std::chrono::operator>`比较时长、同一Clock的时间点或所列日历字段的`>`关系。

时长语义见[`duration`](chrono_duration.md)。日历有效性由相应类型的`ok()`判断。

## 函数原型

通过`left > right`调用；隐藏友元通过实参相关查找参与，不能依赖限定命名空间查找。

### 原型1

所属类型：[`duration<Rep, Period>`](chrono_duration.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
template <class Rep2, class Period2>
[[nodiscard]] friend constexpr bool operator>(const duration& left, const duration<Rep2, Period2>& right);
```

### 原型2

所属类型：[`time_point<Clock, Duration>`](chrono_time_point.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
template <class Duration2>
[[nodiscard]] friend constexpr bool operator>(const time_point& left, const time_point<Clock, Duration2>& right);
```

### 原型3

所属类型：[`day`](chrono_day.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
[[nodiscard]] friend constexpr bool operator>(const day& left, const day& right) noexcept;
```

### 原型4

所属类型：[`month`](chrono_month.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
[[nodiscard]] friend constexpr bool operator>(const month& left, const month& right) noexcept;
```

### 原型5

所属类型：[`weekday`](chrono_weekday.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
[[nodiscard]] friend constexpr bool operator>(const weekday& left, const weekday& right) noexcept;
```

### 原型6

所属类型：[`year`](chrono_year.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
[[nodiscard]] friend constexpr bool operator>(const year& left, const year& right) noexcept;
```

### 原型7

所属类型：[`month_day`](chrono_month_day.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
[[nodiscard]] friend constexpr bool operator>(const month_day& left, const month_day& right) noexcept;
```

### 原型8

所属类型：[`month_day_last`](chrono_month_day_last.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
[[nodiscard]] friend constexpr bool operator>(const month_day_last& left, const month_day_last& right) noexcept;
```

### 原型9

所属类型：[`year_month`](chrono_year_month.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
[[nodiscard]] friend constexpr bool operator>(const year_month& left, const year_month& right) noexcept;
```

### 原型10

所属类型：[`year_month_day`](chrono_year_month_day.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
[[nodiscard]] friend constexpr bool operator>(const year_month_day& left, const year_month_day& right) noexcept;
```

### 原型11

所属类型：[`year_month_day_last`](chrono_year_month_day_last.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
[[nodiscard]] friend constexpr bool operator>(const year_month_day_last& left, const year_month_day_last& right) noexcept;
```

## 参数说明

### 原型1的参数

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

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Duration2` | 另一时间点保存的duration类型；两个时间点的Clock相同。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 时间点；参与同一Clock的比较或偏移，结果精度由公共duration决定。 |
| `right` | 输入 | 时间点；参与同一Clock的比较或偏移，结果精度由公共duration决定。 |

### 原型3的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 日字段，通常为1到31；不携带月份或年份。 |
| `right` | 输入 | 日字段，通常为1到31；不携带月份或年份。 |

### 原型4的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 月字段，1到12分别表示一月至十二月。 |
| `right` | 输入 | 月字段，1到12分别表示一月至十二月。 |

### 原型5的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 星期字段，C编码0为星期日、1到6为星期一至星期六。 |
| `right` | 输入 | 星期字段，C编码0为星期日、1到6为星期一至星期六。 |

### 原型6的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 年字段，有效范围为-32767到32767。 |
| `right` | 输入 | 年字段，有效范围为-32767到32767。 |

### 原型7的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 月与日字段的组合，不含年份。 |
| `right` | 输入 | 月与日字段的组合，不含年份。 |

### 原型8的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 某月最后一天的标签组合。 |
| `right` | 输入 | 某月最后一天的标签组合。 |

### 原型9的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 年份与月份的组合。 |
| `right` | 输入 | 年份与月份的组合。 |

### 原型10的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 年、月、日字段；按字段运算，不自动校正无效日期。 |
| `right` | 输入 | 年、月、日字段；按字段运算，不自动校正无效日期。 |

### 原型11的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 某年某月的最后一天。 |
| `right` | 输入 | 某年某月的最后一天。 |

## 返回值说明

| 适用原型 | 返回类型 | 含义 |
| --- | --- | --- |
| 原型1 | `bool` | 按公共计时周期比较两个计数，判断所示关系。 |
| 原型2 | `bool` | 比较同一Clock下的time_since_epoch()时长，判断所示关系。 |
| 原型3 | `bool` | 比较保存的对应日历字段；组合字段按年、月、日或星期成员顺序判断关系，不转换为时间戳。 |
| 原型4 | `bool` | 比较保存的对应日历字段；组合字段按年、月、日或星期成员顺序判断关系，不转换为时间戳。 |
| 原型5 | `bool` | 比较保存的对应日历字段；组合字段按年、月、日或星期成员顺序判断关系，不转换为时间戳。 |
| 原型6 | `bool` | 比较保存的对应日历字段；组合字段按年、月、日或星期成员顺序判断关系，不转换为时间戳。 |
| 原型7 | `bool` | 比较保存的对应日历字段；组合字段按年、月、日或星期成员顺序判断关系，不转换为时间戳。 |
| 原型8 | `bool` | 比较保存的对应日历字段；组合字段按年、月、日或星期成员顺序判断关系，不转换为时间戳。 |
| 原型9 | `bool` | 比较保存的对应日历字段；组合字段按年、月、日或星期成员顺序判断关系，不转换为时间戳。 |
| 原型10 | `bool` | 比较保存的对应日历字段；组合字段按年、月、日或星期成员顺序判断关系，不转换为时间戳。 |
| 原型11 | `bool` | 比较保存的对应日历字段；组合字段按年、月、日或星期成员顺序判断关系，不转换为时间戳。 |

## 约束说明

- 计数及中间运算须可表示。
- 日历运算不隐式校正无效日期；结果是否有效由相应类型的`ok()`判断。
- 两个时间点仅能在相同Clock下运算或比较。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/chrono>

bool example()
{
    const asc::std::chrono::seconds left{1};
    const asc::std::chrono::milliseconds right{1000};
    const auto earlier = asc::std::chrono::year{2024} / asc::std::chrono::month{2};
    const auto later = asc::std::chrono::year{2024} / asc::std::chrono::month{3};
    return (left > right) == false && (earlier > later) == false;
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
