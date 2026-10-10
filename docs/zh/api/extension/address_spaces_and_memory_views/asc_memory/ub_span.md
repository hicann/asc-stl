# asc::ub_span

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

头文件路径为：`<asc/memory>`。

`asc::ub_span<T>` 是不拥有存储的 UB 连续内存视图，保存首元素指针和元素数量，可用于访问、切片和查询字节数。

## 声明

```cpp
template<class T> class asc::ub_span
```

## 约束说明

- 仅可在 AI Core SIMD 编程中使用
- 视图不管理存储生命周期
- 底层 UB 区域必须在视图使用期间保持有效

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/memory>

void use_type()
{
    using selected = asc::ub_span<int>;
    (void)sizeof(selected);
}
```
