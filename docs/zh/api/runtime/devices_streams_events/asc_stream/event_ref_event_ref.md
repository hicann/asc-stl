# asc::event_ref::event_ref

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

默认构造函数创建空Event引用；带参构造函数包装给定原生句柄但不取得其所有权。

## 函数原型

所属类型：[`asc::event_ref`](event_ref.md)。

### 原型1

```cpp
// asc::event_ref 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr event_ref() noexcept;
```

### 原型2

```cpp
// asc::event_ref 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr explicit event_ref(asc::event_ref::native_handle_type handle) noexcept;
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `handle` | 输入 | Runtime原生句柄（native_handle_type，不透明void指针），不是包装器对象；adopt接管所有权，ref构造仅借用。 |

## 返回值说明

无返回值。

## 约束说明

- 提供可为空的非拥有Host引用。
- 原生句柄为不透明void指针。
- 仅当CANN Runtime调用成功时才更新查询结果和输出参数。

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/stream>

template <class... Args>
asc::event_ref make_object(Args&&... args)
{
    return asc::event_ref(static_cast<Args&&>(args)...);
}
```

对应完整工程使用`C++17`；请在目标工具链及设备上编译和运行。

完整示例源码：[stream_event.cpp](../../../../examples/stream_event.cpp)。

## 关联API

- [`asc::event_ref`](event_ref.md)
- [本头文件的接口列表](asc_stream.md)
