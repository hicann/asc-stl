# asc::device_ref::device_ref

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

`asc::device_ref` 构造函数使用给定的零基 Runtime Device 序号创建引用值。

## 函数原型

```cpp
constexpr explicit asc::device_ref::device_ref(asc::std::uint32_t ordinal) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `ordinal` | 输入 | Runtime Device 序号（uint32_t，0 起）：引用仅保存该序号，不拥有 Runtime 状态。 |

## 约束说明

- 仅可在 Host 查询或选择 Device
- 引用只保存设备序号且不拥有 Runtime 状态
- 查询失败时输出参数保持原值，属性仅限当前接口列出的 AI Core、Vector Core、Warp、UB、GM、L2 与架构字段

## 调用示例

以下 Host 片段使用具体对象演示调用；涉及资源操作时须遵守本页的初始化和生命周期约束。

```cpp
#include <asc/devices>

void example()
{
    asc::device_ref device(0);
    (void)device.ordinal();
}
```
