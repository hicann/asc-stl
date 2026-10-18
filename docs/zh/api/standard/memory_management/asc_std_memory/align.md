# asc::std::align

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

头文件路径为：`<asc/std/memory>`。

`asc::std::align`在调用方提供的存储区中寻找满足大小与对齐要求的位置。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 函数原型

```cpp
namespace asc::std {
void* align(size_t alignment, size_t size, void*& pointer, size_t& space) noexcept;
} // namespace asc::std
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `alignment` | 输入 | 字节对齐值，须为2的非负整数次幂，例如1、2、4、8。 |
| `size` | 输入 | 在对齐后地址处所需的连续字节数。 |
| `pointer` | 输入/输出 | 输入为可用缓冲区的起点；成功时推进到满足alignment的地址，同时相应减少space，失败时保持两者不变。 |
| `space` | 输入/输出 | 输入为从`pointer`起可用的连续字节数；成功时只扣除起点对齐所消耗的填充字节，不扣除`size`。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `void *` | 返回满足所需对齐的存储地址；空间不足时返回空指针。 |

## 约束说明

- 调用方须提供从`pointer`起至少`space`字节的有效连续存储；本接口不分配内存，也不构造对象。
- `alignment`无效、`pointer`为空、地址取整溢出或剩余空间不足时返回`nullptr`，保持`pointer`和`space`不变。
- 成功时返回对齐后的地址，同时更新`pointer`；`space`仅减去对齐填充字节。

## 调用示例

以下Host示例使用具体对象，并检查调用结果。

```cpp
#include <asc/std/memory>
#include <asc/std/cstddef>

bool example()
{
    alignas(16) unsigned char storage[32]{};
    void* pointer = storage + 1;
    asc::std::size_t space = 31;
    void* result = asc::std::align(16, 8, pointer, space);
    if (result != storage + 16 || pointer != result || space != 16) return false;
    // 对齐已满足，但17字节放不进剩余空间；失败不修改输入输出参数。
    return asc::std::align(16, 17, pointer, space) == nullptr &&
        pointer == result && space == 16;
}
```

## 关联API

- [本头文件的接口列表](asc_std_memory.md)
