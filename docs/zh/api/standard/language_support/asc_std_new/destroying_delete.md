# asc::std::destroying_delete

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

头文件路径为：`<asc/std/new>`。

`asc::std::destroying_delete`是`destroying_delete_t`类型的常量对象，从C++17起可作为普通重载的标签实参使用。

## 声明

```cpp
namespace asc::std {
inline constexpr destroying_delete_t destroying_delete{};
} // namespace asc::std
```

## 约束说明

- 对象本身不持有资源，不执行销毁或释放操作。
- 此词汇不改变编译器的delete表达式或销毁型delete规则。

## 调用示例

以下示例使用普通函数的标签参数，不依赖销毁型delete语法。

```cpp
#include <asc/std/new>

constexpr bool selected(asc::std::destroying_delete_t) { return true; }
static_assert(selected(asc::std::destroying_delete));
```

## 关联API

- [`asc::std::destroying_delete_t`](destroying_delete_t.md)
- [本头文件的接口列表](asc_std_new.md)
