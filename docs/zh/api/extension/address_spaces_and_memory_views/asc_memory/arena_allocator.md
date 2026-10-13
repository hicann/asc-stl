# asc::arena_allocator

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

`asc::arena_allocator<T>` 把 `monotonic_arena` 适配为元素分配器；分配按 `alignof(T)` 对齐，单次 `deallocate` 不回收空间。

`monotonic_arena` 在集中管理的存储上按到达顺序单向分配；空间在 `reset()` 或 arena 生命周期结束后整体回收，单次 `deallocate` 不回收空间。详见 [asc::monotonic_arena](monotonic_arena.md)。

## 声明

```cpp
template<class T> class asc::arena_allocator
```

## 约束说明

- allocator 非拥有地引用 monotonic_arena，arena 必须在 allocator 及其分配结果使用期间保持有效
- 元素数量乘以 sizeof(T) 不得溢出
- 空间不足时 allocate 返回空指针

## 调用示例

以下片段演示 arena 存储、分配器构造、分配与对象读写的完整用法；输入和执行上下文须满足本页约束。

```cpp
#include <asc/memory>

bool use_arena_allocator()
{
    // 准备 arena 使用的存储；Host 片段以本地缓冲为例，设备侧可换成 GM 区域
    unsigned char buffer[128];
    asc::monotonic_arena arena(buffer, sizeof(buffer));

    // 以 arena 构造元素分配器；allocator 非拥有地引用 arena
    asc::arena_allocator<int> allocator(arena);

    // 分配 4 个 int；空间不足时 allocate 返回空指针，调用方须判空
    int* data = allocator.allocate(4);
    if (data == nullptr) {
        return false;
    }
    for (int i = 0; i < 4; ++i) {
        data[i] = i + 1;
    }
    const bool ok = data[0] == 1 && data[1] == 2 && data[2] == 3 && data[3] == 4;

    // 单次 deallocate 不回收空间；存储由 arena 统一管理，reset 或 arena 生命周期结束后整体释放
    allocator.deallocate(data, 4);
    return ok;
}
```
