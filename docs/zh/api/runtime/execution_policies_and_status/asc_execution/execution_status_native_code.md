# asc::execution_status::native_code

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

头文件路径为：`<asc/execution>`。

`asc::execution_status::native_code`返回后端Runtime的原生状态码；非`backend_error`状态返回0。

## 函数原型

所属类型：[`asc::execution_status`](execution_status.md)。

```cpp
// asc::execution_status 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr int native_code() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `int` | 返回后端Runtime的原生状态码。 |

## 约束说明

- 仅可在Host使用。
- 状态值可平凡复制。
- 成功状态的code()为execution_errc::success，native_code()为0，失败状态保留可用于诊断的状态码。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/execution>

bool example()
{
    asc::execution_status success;
    asc::execution_status failure(asc::execution_errc::backend_error, 17);
    return success.success() && success.code() == asc::execution_errc::success && success.native_code() == 0
        && !failure.success() && failure.code() == asc::execution_errc::backend_error && failure.native_code() == 17;
}
```

## 关联API

- [`asc::execution_status`](execution_status.md)：参数校验和任务提交状态；提交成功不表示异步工作已经完成。
