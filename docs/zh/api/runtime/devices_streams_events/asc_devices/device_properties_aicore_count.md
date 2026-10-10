# asc::device_properties::aicore_count

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

头文件路径为：`<asc/devices>`。

`asc::device_properties::aicore_count` 保存 Device 的 AICore 数量。

## 声明

```cpp
asc::std::uint32_t asc::device_properties::aicore_count
```

## 约束说明

- 仅可在 Host 查询或选择 Device
- 引用只保存设备序号且不拥有 Runtime 状态
- 查询失败时输出参数保持原值，属性仅限当前接口列出的 AI Core、Vector Core、Warp、UB、GM、L2 与架构字段

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/devices>

void example(const asc::device_properties& object)
{
    (void)object.aicore_count;
}
```
