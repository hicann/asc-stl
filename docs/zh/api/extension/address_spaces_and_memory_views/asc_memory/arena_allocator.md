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

`asc::arena_allocator<T>`把`monotonic_arena`适配为元素分配器；分配按`alignof(T)`对齐，单次`deallocate`不回收空间。

`monotonic_arena`在集中管理的存储上按到达顺序单向分配；`reset()`仅重置分配位置，不销毁对象也不释放底层存储；arena不拥有底层存储，析构不释放它。调用方负责对象的销毁和存储的释放，单次`deallocate`不回收空间。详见[asc::monotonic_arena](monotonic_arena.md)。

## 声明

```cpp
namespace asc {
template<class T> class arena_allocator;
} // namespace asc
```

## 约束说明

- allocator非拥有地引用monotonic_arena，arena必须在allocator及其分配结果使用期间保持有效。
- 元素数量乘以sizeof(T)不得溢出。
- 空间不足时allocate返回空指针。

## 调用示例

以下Host示例在调用方提供的存储中构造四个整数，并在重置arena前结束对象生命周期。

```cpp
#include <asc/memory>
#include <asc/std/memory>

bool use_arena_allocator()
{
    alignas(int) unsigned char storage[128];
    asc::monotonic_arena arena(storage, sizeof(storage));
    asc::arena_allocator<int> allocator(arena);
    int* values = allocator.allocate(4);
    if (values == nullptr) {
        return false;
    }
    for (int i = 0; i < 4; ++i) {
        asc::std::construct_at(values + i, i + 1);
    }
    const bool ok = values[0] == 1 && values[3] == 4;
    asc::std::destroy_n(values, 4);
    allocator.deallocate(values, 4);
    arena.reset();
    // reset 只允许重新使用存储；storage 的生命周期由本函数管理。
    return ok && arena.used() == 0;
}
```

## 关联API

- [本头文件的接口列表](asc_memory.md)
