# asc::binary_semaphore

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

头文件路径为：`<asc/semaphore>`。

`asc::binary_semaphore`把最大计数固定为1的counting_semaphore别名。

## 声明

```cpp
namespace asc {
template<asc::memory_scope Scope> using binary_semaphore = asc::counting_semaphore<Scope, 1>;
} // namespace asc
```

## 约束说明

- 使用C++17。
- 在AI Core SIMT编程 中操作调用方管理的GM状态。
- Scope必须为asc::memory_scope::block或asc::memory_scope::device。
- 所有阻塞参与者必须能够并发推进。
- 复制构造和复制赋值已删除。

## 调用示例

以下片段在调用方提供的对齐GM存储中初始化二值信号量，再演示非阻塞获取及配对释放。初始化由指定线程完成，发布后参与线程才能访问对象。

```cpp
#include <asc/semaphore>
#include <asc/std/new>

using semaphore_type = asc::binary_semaphore<asc::memory_scope::device>;

// A single designated thread initializes aligned GM storage before publication.
__aicore__ void initialize(semaphore_type* gm_storage)
{
    ::new (static_cast<void*>(gm_storage)) semaphore_type(1);
}

// gm_semaphore points to an initialized GM object visible to all participants.
__aicore__ bool example(semaphore_type* gm_semaphore)
{
    static_assert(semaphore_type::max() == 1);
    const bool acquired = gm_semaphore->try_acquire();
    if (acquired)
        gm_semaphore->release();
    return acquired;
}
```

## 关联API

- [本头文件的接口列表](asc_semaphore.md)
