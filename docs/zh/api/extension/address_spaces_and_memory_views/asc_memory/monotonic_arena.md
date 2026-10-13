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

`asc::monotonic_arena`在调用方提供的连续存储中按对齐要求单向分配内存。单次分配不能释放，`reset()`可一次性复用全部容量。

## 声明

```cpp
namespace asc {
class monotonic_arena;
} // namespace asc
```

## 约束说明

- 底层存储由调用方拥有并须在arena使用期间保持有效。
- alignment必须是非零的2的幂。
- 空间不足时allocate返回空指针。
- reset后此前取得的分配不得继续使用。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/memory>

bool example()
{
    alignas(16) unsigned char storage[64]{};
    asc::monotonic_arena arena(storage, sizeof(storage));
    void* first = arena.allocate(16, 16);
    void* second = arena.allocate(16, 16);
    return first == storage && second == storage + 16;
}
```

## 关联API

- [本头文件的接口列表](asc_memory.md)
