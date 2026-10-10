# asc::args::runtime_bounds::upper

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

头文件路径为：`<asc/argument>`。

`asc::args::runtime_bounds::upper` 返回边界对象保存或编码的上界。

## 函数原型

```cpp
constexpr T asc::args::runtime_bounds::upper() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回边界对象保存或编码的上界。 |

## 约束说明

- 使用 C++17，可在 Host、AI Core SIMD 编程 和 AI Core SIMT 编程中使用
- Bounds 必须为 asc::args::no_bounds 或 asc::args::static_bounds
- 延迟指针在使用时不得为空，调用方存储必须覆盖整个使用周期

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/argument>

void example(asc::args::runtime_bounds<int>& object)
{
    (void)object.upper();
}
```
