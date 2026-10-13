# asc::pinned_buffer

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

头文件路径为：`<asc/buffer>`。

`asc::pinned_buffer<T>`是Host侧使用的页锁定内存拥有者，用于管理一段连续的、元素类型为`T`的Host可访问存储。类型只支持可平凡复制的元素，不可复制但可以移动。

## 声明

```cpp
namespace asc {
template<class T> class pinned_buffer;
} // namespace asc
```

## 约束说明

- T必须为可平凡复制类型。
- 对象不可复制但可移动。
- 创建时使用的Stream和内存资源必须在对象关闭前保持有效。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/buffer>

bool example()
{
    asc::pinned_buffer<int> buffer;
    return buffer.empty() && buffer.size() == 0 && buffer.data() == nullptr;
}
```

## 关联API

- [本头文件的接口列表](asc_buffer.md)
