# asc::gm_span

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

`asc::gm_span<T>` 是不拥有存储的 GM 连续内存视图，保存首元素指针和元素数量，可用于访问、切片和查询字节数。

GM 指 Global Memory（全局存储），是设备侧可访问的数据空间；视图要求底层存储位于 GM，并在视图使用期间保持可访问。`<asc/memory>` 提供的内存视图与内存空间接口总述见 [asc/memory 头文件说明](asc_memory.md)。

## 声明

```cpp
template<class T> class asc::gm_span
```

## 约束说明

- 视图不管理存储生命周期
- 底层 GM 区域必须在视图使用期间保持有效
- 索引和切片范围由调用方保证有效

## 调用示例

以下片段演示视图构造、大小查询、元素访问与切片；输入和执行上下文须满足本页约束。

```cpp
#include <asc/memory>

bool use_gm_span()
{
    // 视图不拥有存储：Host 片段以本地数组充当底层存储，设备侧则指向 GM 区域；
    // 底层存储必须在视图使用期间保持有效
    int storage[4] = {1, 2, 3, 4};
    asc::gm_span<int> view(storage, 4);

    bool ok = view.size() == 4 && !view.empty();
    ok = ok && view.size_bytes() == 4 * sizeof(int);
    ok = ok && view.data()[0] == 1 && view[1] == 2;  // 数据指针与下标访问
    ok = ok && view.first(2)[1] == 2;                // 切片：前 2 个元素
    ok = ok && view.last(1)[0] == 4;                 // 切片：后 1 个元素
    ok = ok && view.subspan(1, 2)[0] == 2;           // 切片：偏移 1 起 2 个元素
    return ok;
}
```
