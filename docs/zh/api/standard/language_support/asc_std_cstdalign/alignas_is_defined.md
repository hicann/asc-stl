# __alignas_is_defined

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

头文件路径为：`<asc/std/cstdalign>`。

`__alignas_is_defined`在C++17模式提供值为1的C兼容功能宏，用于检查对齐关键字的C++兼容定义。

## 声明

```cpp
#define __alignas_is_defined 1
```

## 约束说明

- 本库仅在C++17模式补充该宏，C++20及以上模式仍可包含头文件，但不由本库新增该宏。
- 如果此前的系统头已经定义该宏，本库保留其定义，不主动重定义或删除。

## 调用示例

以下片段适用于C++17。

```cpp
#include <asc/std/cstdalign>

static_assert(__alignas_is_defined == 1);
```

## 关联API

- [本头文件的接口列表](asc_std_cstdalign.md)
