# asc::std::timespec_get

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

头文件路径为：`<asc/std/ctime>`。

`asc::std::timespec_get` 由 `<asc/std/ctime>` 提供，host-only 基准时间获取，转发 ::timespec_get，base 为 TIME_UTC

标准语义参考：[cppreference `ctime`](https://en.cppreference.com/w/cpp/header/ctime)。

## 函数原型

```cpp
int timespec_get(timespec* ts, int base) noexcept
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `ts` | 输入 | 指向参与操作的数据；指针可访问范围和生命周期须满足约束说明。 |
| `base` | 输入 | 控制本次操作的标量值；有效取值由声明和约束说明共同确定。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `按声明确定` | 返回该操作产生的值，具体含义由所选原型确定。 |

## 约束说明

- 返回纪元以来的日历时间数值，宿主侧可用

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/ctime>

decltype(auto) example(timespec* ts, int base)
{
    return asc::std::timespec_get(ts, base);
}
```
