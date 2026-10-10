# asc::monotonic_arena

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

`asc::monotonic_arena` 在调用方提供的连续存储中按对齐要求单向分配内存。单次分配不能释放，`reset()` 可一次性复用全部容量。

## 声明

```cpp
class asc::monotonic_arena
```

## 约束说明

- 底层存储由调用方拥有并须在 arena 使用期间保持有效
- alignment 必须是非零的 2 的幂
- 空间不足时 allocate 返回空指针
- reset 后此前取得的分配不得继续使用

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/memory>

void use_type(const asc::monotonic_arena& value)
{
    (void)value;
}
```
