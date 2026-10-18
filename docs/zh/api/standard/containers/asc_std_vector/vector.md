# asc::std::vector

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

头文件路径为：`<asc/std/vector>`。

`asc::std::vector`在连续存储中保存可增长的元素序列。

标准语义参考：[cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector)。

## 声明

```cpp
namespace asc::std {
template<class T, class Allocator> class vector;
} // namespace asc::std
```

## 约束说明

- 构造时显式提供`Allocator`对象；分配器须能为`T`提供和释放连续存储。
- `operator[]`的下标须小于`size()`；调用`front()`、`back()`或`pop_back()`前须非空。
- 插入可能导致扩容；分配器和元素类型须支持相应分配、构造及移动操作。扩容会使指向原存储的指针、引用和迭代器失效。
- 在Device侧使用时，所调用的分配器及元素操作须在相应编程模式可用，且不得抛出异常；使用前须保证分配能够成功，或已预留足够容量。
- 当前移动赋值释放目标原存储、复制源分配器并接管源存储，使源容器变为空；它不按分配器传播特征选择逐元素移动路径。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <memory>
#include <asc/std/vector>

bool example()
{
    asc::std::vector<int, ::std::allocator<int>> values(::std::allocator<int>{});
    values.push_back(1);
    values.push_back(3);
    values[1] = 7;
    return values.size() == 2 && values[0] == 1 && values[1] == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_vector.md)
