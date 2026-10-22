# asc::thread_extents_3d

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

头文件路径为：`<asc/hierarchy>`。

`asc::thread_extents_3d`返回当前Block内的三维线程范围blockDim。

## 函数原型

```cpp
namespace asc {
asc::extent3d thread_extents_3d() noexcept;
}  // namespace asc
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::extent3d` | 返回由当前网格和线程块尺寸构成的执行层次或启动尺寸。 |

## 约束说明

- 仅可在AI Core SIMT编程中调用。
- 必须在正在执行的AI Core SIMT核函数内查询；结果取自当前启动配置，本函数不执行线程同步。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/hierarchy>

__aicore__ decltype(auto) example()
{
    return asc::thread_extents_3d();
}
```

## 关联API

- [本头文件的接口列表](asc_hierarchy.md)
