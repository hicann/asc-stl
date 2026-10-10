# asc::memory_resource_properties::memory_resource_properties

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

头文件路径为：`<asc/memory_resource>`。

`asc::memory_resource_properties` 构造函数保存 Host 可访问性、Device 可访问性和最大字节对齐三个资源属性。

## 函数原型

```cpp
constexpr asc::memory_resource_properties::memory_resource_properties(bool host_accessible, bool device_accessible, asc::std::size_t maximum_alignment) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `host_accessible` | 输入 | 指定“构造函数保存 Host 可访问性、Device 可访问性和最大字节对齐三个资源属性”使用的标量值；取值须满足声明和约束。 |
| `device_accessible` | 输入 | 指定“构造函数保存 Host 可访问性、Device 可访问性和最大字节对齐三个资源属性”使用的标量值；取值须满足声明和约束。 |
| `maximum_alignment` | 输入 | 要求的对齐值，单位为字节。 |

## 约束说明

- 仅可在 Host 调用
- 内存资源不抛出异常
- 分配大小、对齐和输出指针必须有效，释放时须使用同一资源及原始大小和对齐
- 资源及其引用的生命周期由调用方管理

## 调用示例

以下 Host 片段使用具体对象演示调用；涉及资源操作时须遵守本页的初始化和生命周期约束。

```cpp
#include <asc/memory_resource>

void example()
{
    asc::memory_resource_properties properties(true, true, 64);
    (void)properties.maximum_alignment();
}
```
