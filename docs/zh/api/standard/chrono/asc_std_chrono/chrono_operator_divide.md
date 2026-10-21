# asc::std::chrono::`operator/`

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

`asc::std::chrono::operator/`对时长做除法，或用日历字段组装月日、年月、完整日期及第n个/最后一个星期描述。

时长语义见[`duration`](chrono_duration.md)。日历有效性由相应类型的`ok()`判断。

## 函数原型

通过`left / right`调用；隐藏友元通过实参相关查找参与，不能依赖限定命名空间查找。

### 原型1

所属类型：[`duration<Rep, Period>`](chrono_duration.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。声明摘要省略仅供重载选择的实现参数：`Rep2`不得为`duration`，且`const Rep2&`须能转换到`common_type_t<Rep, Rep2>`。

```cpp
template <class Rep2>
[[nodiscard]] friend constexpr duration<common_type_t<Rep, Rep2>, Period> operator/(const duration& left, const Rep2& right);
```

### 原型2

所属类型：[`duration<Rep, Period>`](chrono_duration.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
template <class Rep2, class Period2>
[[nodiscard]] friend constexpr common_type_t<Rep, Rep2> operator/(const duration& left, const duration<Rep2, Period2>& right);
```

### 原型3

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr month_day operator/(const chrono::month& left, const chrono::day& right) noexcept;
```

### 原型4

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr month_day operator/(const chrono::day& left, const chrono::month& right) noexcept;
```

### 原型5

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr month_day operator/(const chrono::month& left, int right) noexcept;
```

### 原型6

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr month_day operator/(int left, const chrono::day& right) noexcept;
```

### 原型7

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr month_day operator/(const chrono::day& left, int right) noexcept;
```

### 原型8

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr month_day_last operator/(const chrono::month& left, last_spec right) noexcept;
```

### 原型9

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr month_day_last operator/(last_spec left, const chrono::month& right) noexcept;
```

### 原型10

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr month_day_last operator/(int left, last_spec right) noexcept;
```

### 原型11

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr month_day_last operator/(last_spec left, int right) noexcept;
```

### 原型12

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr month_weekday operator/(const chrono::month& left, const chrono::weekday_indexed& right) noexcept;
```

### 原型13

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr month_weekday operator/(int left, const chrono::weekday_indexed& right) noexcept;
```

### 原型14

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr month_weekday operator/(const chrono::weekday_indexed& left, const chrono::month& right) noexcept;
```

### 原型15

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr month_weekday operator/(const chrono::weekday_indexed& left, int right) noexcept;
```

### 原型16

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr month_weekday_last operator/(const chrono::month& left, const chrono::weekday_last& right) noexcept;
```

### 原型17

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr month_weekday_last operator/(int left, const chrono::weekday_last& right) noexcept;
```

### 原型18

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr month_weekday_last operator/(const chrono::weekday_last& left, const chrono::month& right) noexcept;
```

### 原型19

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr month_weekday_last operator/(const chrono::weekday_last& left, int right) noexcept;
```

### 原型20

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month operator/(const chrono::year& left, const chrono::month& right) noexcept;
```

### 原型21

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month operator/(const chrono::year& left, int right) noexcept;
```

### 原型22

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_day operator/(const year_month& left, const day& right) noexcept;
```

### 原型23

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_day operator/(const year_month& left, int right) noexcept;
```

### 原型24

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_day operator/(const year& left, const month_day& right) noexcept;
```

### 原型25

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_day operator/(int left, const month_day& right) noexcept;
```

### 原型26

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_day operator/(const month_day& left, const year& right) noexcept;
```

### 原型27

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_day operator/(const month_day& left, int right) noexcept;
```

### 原型28

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_day_last operator/(const year_month& left, last_spec right) noexcept;
```

### 原型29

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_day_last operator/(const year& left, const month_day_last& right) noexcept;
```

### 原型30

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_day_last operator/(int left, const month_day_last& right) noexcept;
```

### 原型31

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_day_last operator/(const month_day_last& left, const year& right) noexcept;
```

### 原型32

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_day_last operator/(const month_day_last& left, int right) noexcept;
```

### 原型33

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_weekday operator/(const year_month& left, const weekday_indexed& right) noexcept;
```

### 原型34

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_weekday operator/(const year& left, const month_weekday& right) noexcept;
```

### 原型35

位于`asc::std::chrono`命名空间。

```cpp
constexpr year_month_weekday operator/(int left, const month_weekday& right) noexcept;
```

### 原型36

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_weekday operator/(const month_weekday& left, const year& right) noexcept;
```

### 原型37

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_weekday operator/(const month_weekday& left, int right) noexcept;
```

### 原型38

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_weekday_last operator/(const year_month& left, const weekday_last& right) noexcept;
```

### 原型39

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_weekday_last operator/(const year& left, const month_weekday_last& right) noexcept;
```

### 原型40

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_weekday_last operator/(int left, const month_weekday_last& right) noexcept;
```

### 原型41

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_weekday_last operator/(const month_weekday_last& left, const year& right) noexcept;
```

### 原型42

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_weekday_last operator/(const month_weekday_last& left, int right) noexcept;
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

### 原型3的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 月字段，1到12分别表示一月至十二月。 |
| `right` | 输入 | 日字段，通常为1到31；不携带月份或年份。 |

### 原型4的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 日字段，通常为1到31；不携带月份或年份。 |
| `right` | 输入 | 月字段，1到12分别表示一月至十二月。 |

### 原型5的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 月字段，1到12分别表示一月至十二月。 |
| `right` | 输入 | 按日字段构造的整数值；有效域与对应日历字段相同。 |

### 原型6的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 按月份字段构造的整数值；有效域与对应日历字段相同。 |
| `right` | 输入 | 日字段，通常为1到31；不携带月份或年份。 |

### 原型7的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 日字段，通常为1到31；不携带月份或年份。 |
| `right` | 输入 | 按月份字段构造的整数值；有效域与对应日历字段相同。 |

### 原型8的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 月字段，1到12分别表示一月至十二月。 |
| `right` | 输入 | 月末标签，不保存具体日数或星期。 |

### 原型9的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 月末标签，不保存具体日数或星期。 |
| `right` | 输入 | 月字段，1到12分别表示一月至十二月。 |

### 原型10的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 按月份字段构造的整数值；有效域与对应日历字段相同。 |
| `right` | 输入 | 月末标签，不保存具体日数或星期。 |

### 原型11的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 月末标签，不保存具体日数或星期。 |
| `right` | 输入 | 按月份字段构造的整数值；有效域与对应日历字段相同。 |

### 原型12的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 月字段，1到12分别表示一月至十二月。 |
| `right` | 输入 | 星期与该月内序号的组合；序号1到5表示第几个该星期。 |

### 原型13的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 按月份字段构造的整数值；有效域与对应日历字段相同。 |
| `right` | 输入 | 星期与该月内序号的组合；序号1到5表示第几个该星期。 |

### 原型14的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 星期与该月内序号的组合；序号1到5表示第几个该星期。 |
| `right` | 输入 | 月字段，1到12分别表示一月至十二月。 |

### 原型15的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 星期与该月内序号的组合；序号1到5表示第几个该星期。 |
| `right` | 输入 | 按月份字段构造的整数值；有效域与对应日历字段相同。 |

### 原型16的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 月字段，1到12分别表示一月至十二月。 |
| `right` | 输入 | 该月最后一次出现的指定星期。 |

### 原型17的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 按月份字段构造的整数值；有效域与对应日历字段相同。 |
| `right` | 输入 | 该月最后一次出现的指定星期。 |

### 原型18的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 该月最后一次出现的指定星期。 |
| `right` | 输入 | 月字段，1到12分别表示一月至十二月。 |

### 原型19的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 该月最后一次出现的指定星期。 |
| `right` | 输入 | 按月份字段构造的整数值；有效域与对应日历字段相同。 |

### 原型20的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 年字段，有效范围为-32767到32767。 |
| `right` | 输入 | 月字段，1到12分别表示一月至十二月。 |

### 原型21的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 年字段，有效范围为-32767到32767。 |
| `right` | 输入 | 按月份字段构造的整数值；有效域与对应日历字段相同。 |

### 原型22的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 年份与月份的组合。 |
| `right` | 输入 | 日字段，通常为1到31；不携带月份或年份。 |

### 原型23的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 年份与月份的组合。 |
| `right` | 输入 | 按日字段构造的整数值；有效域与对应日历字段相同。 |

### 原型24的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 年字段，有效范围为-32767到32767。 |
| `right` | 输入 | 月与日字段的组合，不含年份。 |

### 原型25的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 按年份字段构造的整数值；有效域与对应日历字段相同。 |
| `right` | 输入 | 月与日字段的组合，不含年份。 |

### 原型26的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 月与日字段的组合，不含年份。 |
| `right` | 输入 | 年字段，有效范围为-32767到32767。 |

### 原型27的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 月与日字段的组合，不含年份。 |
| `right` | 输入 | 按年份字段构造的整数值；有效域与对应日历字段相同。 |

### 原型28的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 年份与月份的组合。 |
| `right` | 输入 | 月末标签，不保存具体日数或星期。 |

### 原型29的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 年字段，有效范围为-32767到32767。 |
| `right` | 输入 | 某月最后一天的标签组合。 |

### 原型30的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 按年份字段构造的整数值；有效域与对应日历字段相同。 |
| `right` | 输入 | 某月最后一天的标签组合。 |

### 原型31的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 某月最后一天的标签组合。 |
| `right` | 输入 | 年字段，有效范围为-32767到32767。 |

### 原型32的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 某月最后一天的标签组合。 |
| `right` | 输入 | 按年份字段构造的整数值；有效域与对应日历字段相同。 |

### 原型33的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 年份与月份的组合。 |
| `right` | 输入 | 星期与该月内序号的组合；序号1到5表示第几个该星期。 |

### 原型34的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 年字段，有效范围为-32767到32767。 |
| `right` | 输入 | 月份与第n个星期的组合。 |

### 原型35的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 按年份字段构造的整数值；有效域与对应日历字段相同。 |
| `right` | 输入 | 月份与第n个星期的组合。 |

### 原型36的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 月份与第n个星期的组合。 |
| `right` | 输入 | 年字段，有效范围为-32767到32767。 |

### 原型37的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 月份与第n个星期的组合。 |
| `right` | 输入 | 按年份字段构造的整数值；有效域与对应日历字段相同。 |

### 原型38的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 年份与月份的组合。 |
| `right` | 输入 | 该月最后一次出现的指定星期。 |

### 原型39的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 年字段，有效范围为-32767到32767。 |
| `right` | 输入 | 月份与最后一个指定星期的组合。 |

### 原型40的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 按年份字段构造的整数值；有效域与对应日历字段相同。 |
| `right` | 输入 | 月份与最后一个指定星期的组合。 |

### 原型41的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 月份与最后一个指定星期的组合。 |
| `right` | 输入 | 年字段，有效范围为-32767到32767。 |

### 原型42的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 月份与最后一个指定星期的组合。 |
| `right` | 输入 | 按年份字段构造的整数值；有效域与对应日历字段相同。 |

## 返回值说明

| 适用原型 | 返回类型 | 含义 |
| --- | --- | --- |
| 原型1 | `duration<common_type_t<Rep, Rep2>, Period>` | 时长计数除以标量，返回保持原period的duration。 |
| 原型2 | `common_type_t<Rep, Rep2>` | 两时长换成公共周期后相除，返回公共计数类型的无量纲商。 |
| 原型3 | `month_day` | 将两侧日历字段或标签组装为month_day；不执行数值除法。 |
| 原型4 | `month_day` | 将两侧日历字段或标签组装为month_day；不执行数值除法。 |
| 原型5 | `month_day` | 将两侧日历字段或标签组装为month_day；不执行数值除法。 |
| 原型6 | `month_day` | 将两侧日历字段或标签组装为month_day；不执行数值除法。 |
| 原型7 | `month_day` | 将两侧日历字段或标签组装为month_day；不执行数值除法。 |
| 原型8 | `month_day_last` | 将两侧日历字段或标签组装为month_day_last；不执行数值除法。 |
| 原型9 | `month_day_last` | 将两侧日历字段或标签组装为month_day_last；不执行数值除法。 |
| 原型10 | `month_day_last` | 将两侧日历字段或标签组装为month_day_last；不执行数值除法。 |
| 原型11 | `month_day_last` | 将两侧日历字段或标签组装为month_day_last；不执行数值除法。 |
| 原型12 | `month_weekday` | 将两侧日历字段或标签组装为month_weekday；不执行数值除法。 |
| 原型13 | `month_weekday` | 将两侧日历字段或标签组装为month_weekday；不执行数值除法。 |
| 原型14 | `month_weekday` | 将两侧日历字段或标签组装为month_weekday；不执行数值除法。 |
| 原型15 | `month_weekday` | 将两侧日历字段或标签组装为month_weekday；不执行数值除法。 |
| 原型16 | `month_weekday_last` | 将两侧日历字段或标签组装为month_weekday_last；不执行数值除法。 |
| 原型17 | `month_weekday_last` | 将两侧日历字段或标签组装为month_weekday_last；不执行数值除法。 |
| 原型18 | `month_weekday_last` | 将两侧日历字段或标签组装为month_weekday_last；不执行数值除法。 |
| 原型19 | `month_weekday_last` | 将两侧日历字段或标签组装为month_weekday_last；不执行数值除法。 |
| 原型20 | `year_month` | 将两侧日历字段或标签组装为year_month；不执行数值除法。 |
| 原型21 | `year_month` | 将两侧日历字段或标签组装为year_month；不执行数值除法。 |
| 原型22 | `year_month_day` | 将两侧日历字段或标签组装为year_month_day；不执行数值除法。 |
| 原型23 | `year_month_day` | 将两侧日历字段或标签组装为year_month_day；不执行数值除法。 |
| 原型24 | `year_month_day` | 将两侧日历字段或标签组装为year_month_day；不执行数值除法。 |
| 原型25 | `year_month_day` | 将两侧日历字段或标签组装为year_month_day；不执行数值除法。 |
| 原型26 | `year_month_day` | 将两侧日历字段或标签组装为year_month_day；不执行数值除法。 |
| 原型27 | `year_month_day` | 将两侧日历字段或标签组装为year_month_day；不执行数值除法。 |
| 原型28 | `year_month_day_last` | 将两侧日历字段或标签组装为year_month_day_last；不执行数值除法。 |
| 原型29 | `year_month_day_last` | 将两侧日历字段或标签组装为year_month_day_last；不执行数值除法。 |
| 原型30 | `year_month_day_last` | 将两侧日历字段或标签组装为year_month_day_last；不执行数值除法。 |
| 原型31 | `year_month_day_last` | 将两侧日历字段或标签组装为year_month_day_last；不执行数值除法。 |
| 原型32 | `year_month_day_last` | 将两侧日历字段或标签组装为year_month_day_last；不执行数值除法。 |
| 原型33 | `year_month_weekday` | 将两侧日历字段或标签组装为year_month_weekday；不执行数值除法。 |
| 原型34 | `year_month_weekday` | 将两侧日历字段或标签组装为year_month_weekday；不执行数值除法。 |
| 原型35 | `year_month_weekday` | 将两侧日历字段或标签组装为year_month_weekday；不执行数值除法。 |
| 原型36 | `year_month_weekday` | 将两侧日历字段或标签组装为year_month_weekday；不执行数值除法。 |
| 原型37 | `year_month_weekday` | 将两侧日历字段或标签组装为year_month_weekday；不执行数值除法。 |
| 原型38 | `year_month_weekday_last` | 将两侧日历字段或标签组装为year_month_weekday_last；不执行数值除法。 |
| 原型39 | `year_month_weekday_last` | 将两侧日历字段或标签组装为year_month_weekday_last；不执行数值除法。 |
| 原型40 | `year_month_weekday_last` | 将两侧日历字段或标签组装为year_month_weekday_last；不执行数值除法。 |
| 原型41 | `year_month_weekday_last` | 将两侧日历字段或标签组装为year_month_weekday_last；不执行数值除法。 |
| 原型42 | `year_month_weekday_last` | 将两侧日历字段或标签组装为year_month_weekday_last；不执行数值除法。 |

## 约束说明

- 计数及中间运算须可表示。
- 日历运算不隐式校正无效日期；结果是否有效由相应类型的`ok()`判断。
- 对整型计数，当前实现把转换后为0的除数按1处理；这不是标准chrono的零除数保证。需要标准可移植语义时使用非零除数；有符号最小值除以-1不可表示时不得调用。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/chrono>

bool example()
{
    const auto last_day = asc::std::chrono::year{2024} / asc::std::chrono::month{2}
        / asc::std::chrono::last;
    const auto ratio = asc::std::chrono::seconds{7} / asc::std::chrono::seconds{2};
    return ratio == 3 && static_cast<unsigned>(last_day.day()) == 29;
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
