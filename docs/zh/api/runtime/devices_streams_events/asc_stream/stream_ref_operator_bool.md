# asc::stream_ref::operator bool

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

头文件路径为：`<asc/stream>`。

`asc::stream_ref::operator bool` 判断引用是否保存了非空的 Runtime Stream 句柄。

## 函数原型

```cpp
constexpr explicit asc::stream_ref::operator bool() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `explicit` | 当前对象处于有效或有值状态时返回 `true`，否则返回 `false`。 |

## 约束说明

- 提供可为空的非拥有 Host 引用
- 原生句柄为不透明 void 指针
- 仅当 CANN Runtime 调用成功时才更新查询结果和输出参数

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/stream>

template <class T>
void use_type(const T& value)
{
    (void)value;
}
```

对应完整工程使用 `C++17`，并通过Ascend 950 真机编译与运行验证。

完整示例源码：[stream_event.cpp](../../../../examples/stream_event.cpp)。
