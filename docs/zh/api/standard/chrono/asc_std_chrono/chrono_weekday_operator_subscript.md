# asc::std::chrono::weekday::`operator[]`

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

`asc::std::chrono::weekday::operator[]`借助下标语法构造日历辅助类型：带索引形式由本星期几与索引构造`weekday_indexed`（表示本月第几个此星期几），`last_spec`形式构造`weekday_last`（表示本月最后一个此星期几）。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

所属类型：[`asc::std::chrono::weekday`](chrono_weekday.md)。

### 原型1

```cpp
// asc::std::chrono::weekday 类内的声明节选；模板形参和其他成员由所属类提供。
[[nodiscard]] constexpr weekday_indexed operator[](unsigned int index) const noexcept;
```

### 原型2

```cpp
// asc::std::chrono::weekday 类内的声明节选；模板形参和其他成员由所属类提供。
[[nodiscard]] constexpr weekday_last operator[](last_spec index) const noexcept;
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `index` | 输入 | 该月的第几个星期几，取值1到5；与当前星期几组合成weekday_indexed。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `index` | 输入 | last标记（asc::std::chrono::last）；表示取该月的最后一个当前星期几。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `weekday_indexed` | 返回由本星期几与给定索引构造的`weekday_indexed`，表示本月第几个此星期几。 |
| 原型2 | `weekday_last` | 返回由本星期几构造的`weekday_last`，表示本月最后一个此星期几。 |

## 约束说明

- 日历字段和计时值的运算可在Host与支持的AI Core编程模式使用；日期有效性由相应`ok()`成员判断。

## 调用示例

以下Host片段以具体日期或时间类型演示调用；数值须满足本页约束。

```cpp
#include <asc/std/chrono>

bool example()
{
    namespace chrono = asc::std::chrono;
    chrono::weekday value{3};
    const auto second = value[2];
    return second.weekday().c_encoding() == 3 && second.index() == 2;
}
```

## 关联API

- [`asc::std::chrono::weekday`](chrono_weekday.md)
- [本头文件的接口列表](asc_std_chrono.md)
