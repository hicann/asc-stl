# asc::relaxed_atomic_ref

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

头文件路径为：`<asc/atomic>`。

`asc::relaxed_atomic_ref` 非拥有地引用现有对象并固定使用 relaxed 内存序提供原子操作。

## 声明

```cpp
template<class T> class asc::relaxed_atomic_ref
```

## 约束说明

- 仅可在 AI Core SIMT 编程中调用
- 参数类型、取值范围、会合要求和对象生命周期必须满足页面声明

## 调用示例

以下片段用具体模板实参实例化类型；实际对象仍须满足本页构造与生命周期约束。

```cpp
#include <asc/atomic>

__aicore__ void use_type()
{
    using selected = asc::relaxed_atomic_ref<int>;
    (void)sizeof(selected);
}
```
