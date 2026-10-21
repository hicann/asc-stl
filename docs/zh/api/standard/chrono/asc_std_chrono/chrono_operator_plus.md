# asc::std::chrono::`operator+`

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

`asc::std::chrono::operator+`对时长、时间点或日历字段执行加法。时长先统一周期，日期形式按日、月或年偏移。

时长语义见[`duration`](chrono_duration.md)。日历有效性由相应类型的`ok()`判断。

## 函数原型

通过`left + right`调用；隐藏友元通过实参相关查找参与，不能依赖限定命名空间查找。

### 原型1

所属类型：[`duration<Rep, Period>`](chrono_duration.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
template <class Rep2, class Period2>
[[nodiscard]] friend constexpr common_type_t<duration, duration<Rep2, Period2>> operator+(const duration& left, const duration<Rep2, Period2>& right);
```

### 原型2

所属类型：[`time_point<Clock, Duration>`](chrono_time_point.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
template <class Rep2, class Period2>
[[nodiscard]] friend constexpr time_point<Clock, common_type_t<Duration, chrono::duration<Rep2, Period2>>> operator+(const time_point& left, const chrono::duration<Rep2, Period2>& right);
```

### 原型3

所属类型：[`time_point<Clock, Duration>`](chrono_time_point.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
template <class Rep2, class Period2>
[[nodiscard]] friend constexpr time_point<Clock, common_type_t<Duration, chrono::duration<Rep2, Period2>>> operator+(const chrono::duration<Rep2, Period2>& left, const time_point& right);
```

### 原型4

所属类型：[`day`](chrono_day.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
[[nodiscard]] friend constexpr day operator+(const day& left, const days& right) noexcept;
```

### 原型5

所属类型：[`day`](chrono_day.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
[[nodiscard]] friend constexpr day operator+(const days& left, const day& right) noexcept;
```

### 原型6

所属类型：[`month`](chrono_month.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
[[nodiscard]] friend constexpr month operator+(const month& left, const months& right) noexcept;
```

### 原型7

所属类型：[`month`](chrono_month.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
[[nodiscard]] friend constexpr month operator+(const months& left, const month& right) noexcept;
```

### 原型8

所属类型：[`weekday`](chrono_weekday.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
[[nodiscard]] friend constexpr weekday operator+(const weekday& left, const days& right) noexcept;
```

### 原型9

所属类型：[`weekday`](chrono_weekday.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
[[nodiscard]] friend constexpr weekday operator+(const days& left, const weekday& right) noexcept;
```

### 原型10

所属类型：[`year`](chrono_year.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
[[nodiscard]] friend constexpr year operator+(const year& left, const years& right) noexcept;
```

### 原型11

所属类型：[`year`](chrono_year.md)。以下为类内隐藏友元声明，类模板参数（如有）由所属类型提供。

```cpp
[[nodiscard]] friend constexpr year operator+(const years& left, const year& right) noexcept;
```

### 原型12

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month operator+(const year_month& left, const months& right) noexcept;
```

### 原型13

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month operator+(const months& left, const year_month& right) noexcept;
```

### 原型14

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month operator+(const year_month& left, const years& right) noexcept;
```

### 原型15

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month operator+(const years& left, const year_month& right) noexcept;
```

### 原型16

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_day operator+(const year_month_day& left, const months& right) noexcept;
```

### 原型17

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_day operator+(const months& left, const year_month_day& right) noexcept;
```

### 原型18

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_day operator+(const year_month_day& left, const years& right) noexcept;
```

### 原型19

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_day operator+(const years& left, const year_month_day& right) noexcept;
```

### 原型20

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_day_last operator+(const year_month_day_last& left, const months& right) noexcept;
```

### 原型21

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_day_last operator+(const months& left, const year_month_day_last& right) noexcept;
```

### 原型22

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_day_last operator+(const year_month_day_last& left, const years& right) noexcept;
```

### 原型23

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_day_last operator+(const years& left, const year_month_day_last& right) noexcept;
```

### 原型24

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_weekday operator+(const year_month_weekday& left, const months& right) noexcept;
```

### 原型25

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_weekday operator+(const months& left, const year_month_weekday& right) noexcept;
```

### 原型26

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_weekday operator+(const year_month_weekday& left, const years& right) noexcept;
```

### 原型27

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_weekday operator+(const years& left, const year_month_weekday& right) noexcept;
```

### 原型28

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_weekday_last operator+(const year_month_weekday_last& left, const months& right) noexcept;
```

### 原型29

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_weekday_last operator+(const months& left, const year_month_weekday_last& right) noexcept;
```

### 原型30

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_weekday_last operator+(const year_month_weekday_last& left, const years& right) noexcept;
```

### 原型31

位于`asc::std::chrono`命名空间。

```cpp
[[nodiscard]] constexpr year_month_weekday_last operator+(const years& left, const year_month_weekday_last& right) noexcept;
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
| `Rep2` | 另一操作数的计数或标量表示类型；与Rep形成公共计数类型。 |
| `Period2` | 另一时长的tick周期，是以秒为基准的ratio类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 时间点；参与同一Clock的比较或偏移，结果精度由公共duration决定。 |
| `right` | 输入 | 时长值；计数单位由其period决定，与另一时长运算时先形成公共计时周期。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rep2` | 另一操作数的计数或标量表示类型；与Rep形成公共计数类型。 |
| `Period2` | 另一时长的tick周期，是以秒为基准的ratio类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 时长值；计数单位由其period决定，与另一时长运算时先形成公共计时周期。 |
| `right` | 输入 | 时间点；参与同一Clock的比较或偏移，结果精度由公共duration决定。 |

### 原型4的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 日字段，通常为1到31；不携带月份或年份。 |
| `right` | 输入 | 有符号日数，单位为24小时；用于字段偏移时表示日字段移动量。 |

### 原型5的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 有符号日数，单位为24小时；用于字段偏移时表示日字段移动量。 |
| `right` | 输入 | 日字段，通常为1到31；不携带月份或年份。 |

### 原型6的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 月字段，1到12分别表示一月至十二月。 |
| `right` | 输入 | 有符号月数；单独month的结果按12个月回绕，不保存年份进位。 |

### 原型7的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 有符号月数；单独month的结果按12个月回绕，不保存年份进位。 |
| `right` | 输入 | 月字段，1到12分别表示一月至十二月。 |

### 原型8的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 星期字段，C编码0为星期日、1到6为星期一至星期六。 |
| `right` | 输入 | 有符号日数，单位为24小时；用于字段偏移时表示日字段移动量。 |

### 原型9的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 有符号日数，单位为24小时；用于字段偏移时表示日字段移动量。 |
| `right` | 输入 | 星期字段，C编码0为星期日、1到6为星期一至星期六。 |

### 原型10的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 年字段，有效范围为-32767到32767。 |
| `right` | 输入 | 有符号年数；用于日历运算时保留其它字段。 |

### 原型11的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 有符号年数；用于日历运算时保留其它字段。 |
| `right` | 输入 | 年字段，有效范围为-32767到32767。 |

### 原型12的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 年份与月份的组合。 |
| `right` | 输入 | 有符号月数；用于日历运算时按12个月向年份进位。 |

### 原型13的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 有符号月数；用于日历运算时按12个月向年份进位。 |
| `right` | 输入 | 年份与月份的组合。 |

### 原型14的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 年份与月份的组合。 |
| `right` | 输入 | 有符号年数；用于日历运算时保留其它字段。 |

### 原型15的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 有符号年数；用于日历运算时保留其它字段。 |
| `right` | 输入 | 年份与月份的组合。 |

### 原型16的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 年、月、日字段；按字段运算，不自动校正无效日期。 |
| `right` | 输入 | 有符号月数；用于日历运算时按12个月向年份进位。 |

### 原型17的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 有符号月数；用于日历运算时按12个月向年份进位。 |
| `right` | 输入 | 年、月、日字段；按字段运算，不自动校正无效日期。 |

### 原型18的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 年、月、日字段；按字段运算，不自动校正无效日期。 |
| `right` | 输入 | 有符号年数；用于日历运算时保留其它字段。 |

### 原型19的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 有符号年数；用于日历运算时保留其它字段。 |
| `right` | 输入 | 年、月、日字段；按字段运算，不自动校正无效日期。 |

### 原型20的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 某年某月的最后一天。 |
| `right` | 输入 | 有符号月数；用于日历运算时按12个月向年份进位。 |

### 原型21的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 有符号月数；用于日历运算时按12个月向年份进位。 |
| `right` | 输入 | 某年某月的最后一天。 |

### 原型22的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 某年某月的最后一天。 |
| `right` | 输入 | 有符号年数；用于日历运算时保留其它字段。 |

### 原型23的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 有符号年数；用于日历运算时保留其它字段。 |
| `right` | 输入 | 某年某月的最后一天。 |

### 原型24的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 某年某月的第n个指定星期。 |
| `right` | 输入 | 有符号月数；用于日历运算时按12个月向年份进位。 |

### 原型25的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 有符号月数；用于日历运算时按12个月向年份进位。 |
| `right` | 输入 | 某年某月的第n个指定星期。 |

### 原型26的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 某年某月的第n个指定星期。 |
| `right` | 输入 | 有符号年数；用于日历运算时保留其它字段。 |

### 原型27的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 有符号年数；用于日历运算时保留其它字段。 |
| `right` | 输入 | 某年某月的第n个指定星期。 |

### 原型28的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 某年某月最后一个指定星期。 |
| `right` | 输入 | 有符号月数；用于日历运算时按12个月向年份进位。 |

### 原型29的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 有符号月数；用于日历运算时按12个月向年份进位。 |
| `right` | 输入 | 某年某月最后一个指定星期。 |

### 原型30的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 某年某月最后一个指定星期。 |
| `right` | 输入 | 有符号年数；用于日历运算时保留其它字段。 |

### 原型31的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 有符号年数；用于日历运算时保留其它字段。 |
| `right` | 输入 | 某年某月最后一个指定星期。 |

## 返回值说明

| 适用原型 | 返回类型 | 含义 |
| --- | --- | --- |
| 原型1 | `common_type_t<duration, duration<Rep2, Period2>>` | 时长采用公共周期及计数类型；时间点差返回公共duration。 |
| 原型2 | `time_point<Clock, common_type_t<Duration, chrono::duration<Rep2, Period2>>>` | 按时长偏移时间点，保留Clock，结果duration采用公共精度。 |
| 原型3 | `time_point<Clock, common_type_t<Duration, chrono::duration<Rep2, Period2>>>` | 按时长偏移时间点，保留Clock，结果duration采用公共精度。 |
| 原型4 | `day` | 按对应年数或日数偏移字段，不补充其它日历字段；结果须满足可表示性要求。 |
| 原型5 | `day` | 按对应年数或日数偏移字段，不补充其它日历字段；结果须满足可表示性要求。 |
| 原型6 | `month` | 按12个月回绕，结果为1到12的月字段，不记录年份进位。 |
| 原型7 | `month` | 按12个月回绕，结果为1到12的月字段，不记录年份进位。 |
| 原型8 | `weekday` | 按7日回绕，结果为0到6的星期字段。 |
| 原型9 | `weekday` | 按7日回绕，结果为0到6的星期字段。 |
| 原型10 | `year` | 按对应年数或日数偏移字段，不补充其它日历字段；结果须满足可表示性要求。 |
| 原型11 | `year` | 按对应年数或日数偏移字段，不补充其它日历字段；结果须满足可表示性要求。 |
| 原型12 | `year_month` | 按月份或年份偏移组合字段；其它字段或月末标签保持不变，结果日期可能无效，须用ok()检查。 |
| 原型13 | `year_month` | 按月份或年份偏移组合字段；其它字段或月末标签保持不变，结果日期可能无效，须用ok()检查。 |
| 原型14 | `year_month` | 按月份或年份偏移组合字段；其它字段或月末标签保持不变，结果日期可能无效，须用ok()检查。 |
| 原型15 | `year_month` | 按月份或年份偏移组合字段；其它字段或月末标签保持不变，结果日期可能无效，须用ok()检查。 |
| 原型16 | `year_month_day` | 按月份或年份偏移组合字段；其它字段或月末标签保持不变，结果日期可能无效，须用ok()检查。 |
| 原型17 | `year_month_day` | 按月份或年份偏移组合字段；其它字段或月末标签保持不变，结果日期可能无效，须用ok()检查。 |
| 原型18 | `year_month_day` | 按月份或年份偏移组合字段；其它字段或月末标签保持不变，结果日期可能无效，须用ok()检查。 |
| 原型19 | `year_month_day` | 按月份或年份偏移组合字段；其它字段或月末标签保持不变，结果日期可能无效，须用ok()检查。 |
| 原型20 | `year_month_day_last` | 按月份或年份偏移组合字段；其它字段或月末标签保持不变，结果日期可能无效，须用ok()检查。 |
| 原型21 | `year_month_day_last` | 按月份或年份偏移组合字段；其它字段或月末标签保持不变，结果日期可能无效，须用ok()检查。 |
| 原型22 | `year_month_day_last` | 按月份或年份偏移组合字段；其它字段或月末标签保持不变，结果日期可能无效，须用ok()检查。 |
| 原型23 | `year_month_day_last` | 按月份或年份偏移组合字段；其它字段或月末标签保持不变，结果日期可能无效，须用ok()检查。 |
| 原型24 | `year_month_weekday` | 按月份或年份偏移组合字段；其它字段或月末标签保持不变，结果日期可能无效，须用ok()检查。 |
| 原型25 | `year_month_weekday` | 按月份或年份偏移组合字段；其它字段或月末标签保持不变，结果日期可能无效，须用ok()检查。 |
| 原型26 | `year_month_weekday` | 按月份或年份偏移组合字段；其它字段或月末标签保持不变，结果日期可能无效，须用ok()检查。 |
| 原型27 | `year_month_weekday` | 按月份或年份偏移组合字段；其它字段或月末标签保持不变，结果日期可能无效，须用ok()检查。 |
| 原型28 | `year_month_weekday_last` | 按月份或年份偏移组合字段；其它字段或月末标签保持不变，结果日期可能无效，须用ok()检查。 |
| 原型29 | `year_month_weekday_last` | 按月份或年份偏移组合字段；其它字段或月末标签保持不变，结果日期可能无效，须用ok()检查。 |
| 原型30 | `year_month_weekday_last` | 按月份或年份偏移组合字段；其它字段或月末标签保持不变，结果日期可能无效，须用ok()检查。 |
| 原型31 | `year_month_weekday_last` | 按月份或年份偏移组合字段；其它字段或月末标签保持不变，结果日期可能无效，须用ok()检查。 |

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
    const auto elapsed = asc::std::chrono::seconds{2} + asc::std::chrono::milliseconds{500};
    const auto date = (asc::std::chrono::year{2024} / asc::std::chrono::month{12}
        / asc::std::chrono::day{15}) + asc::std::chrono::months{1};
    return elapsed.count() == 2500 && static_cast<int>(date.year()) == 2025
        && static_cast<unsigned>(date.month()) == 1 && static_cast<unsigned>(date.day()) == 15;
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
