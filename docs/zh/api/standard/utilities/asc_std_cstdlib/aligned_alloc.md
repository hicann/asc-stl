# asc::std::aligned_alloc

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

头文件路径为：`<asc/std/cstdlib>`。

`asc::std::aligned_alloc`由`<asc/std/cstdlib>`提供，按字节数与对齐值分配内存，对齐不合法时返回空指针。

标准语义参考：[cppreference `cstdlib`](https://en.cppreference.com/w/cpp/header/cstdlib)。

## 函数原型

```cpp
namespace asc::std {
[[nodiscard]] void* aligned_alloc(size_t nbytes, size_t alignment) noexcept;
}
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `nbytes` | 输入 | 申请的字节数，须为`alignment`的整数倍。 |
| `alignment` | 输入 | 以字节为单位的对齐值，须为2的非负整数次幂，并受宿主C库支持范围限制。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `void*` | 成功返回满足对齐要求的分配地址，失败返回nullptr；须通过 ::std::free释放。 |

## 约束说明

- 仅用于Host，参数顺序是字节数在前、对齐在后。
- `alignment`须为2的非负整数次幂，`nbytes`须为`alignment`的整数倍；不满足时返回`nullptr`。
- 还须满足宿主C库支持的对齐要求；成功的分配需调用 ::std::free释放。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/cstdlib>
#include <asc/std/cstdint>
#include <cstdlib>

bool example()
{
    void* pointer = asc::std::aligned_alloc(64, 32);
    if (pointer == nullptr) return false;
    const bool aligned = reinterpret_cast<asc::std::uintptr_t>(pointer) % 32 == 0;
    ::std::free(pointer);
    return aligned;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cstdlib.md)
