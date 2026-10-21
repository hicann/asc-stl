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

`asc::ub_span<T>`是不拥有存储的UB连续内存视图，保存首元素指针和元素数量，可用于访问、切片和查询字节数。

## 声明

```cpp
namespace asc {
template <class T>
class ub_span;
}  // namespace asc
```

## 约束说明

- D-SIMD下，元素下标访问返回保留UB（__ubuf__） 地址空间及元素const限定的引用；Host下为普通引用。
- AI Core SIMD使用真实UB地址空间；Host可构造普通指针表示以描述或检查布局。Host表示不提供对设备物理UB的访问；AI Core SIMT不提供此类型。
- 视图不管理存储生命周期。
- 底层UB区域必须在视图使用期间保持有效。
- operator[] 的索引范围由调用方保证有效；first/last/subspan 切片采用失效闭合语义，计数或偏移越出 [0, size()] 时返回空视图，不产生回绕指针。

## 调用示例

以下片段用于D-SIMD编译。调用方提供至少4个int的有效UB区域；本视图不负责分配或释放。

```cpp
#include <asc/memory>

__aicore__ bool example(__ubuf__ int* storage)
{
    asc::ub_span<int> values(storage, 4);
    values[1] = 7;
    auto tail = values.subspan(1, 2);
    return tail.size() == 2 && tail[0] == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_memory.md)
