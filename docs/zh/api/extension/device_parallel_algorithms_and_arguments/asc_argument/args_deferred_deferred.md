# asc::args::deferred::deferred

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

头文件路径为：`<asc/argument>`。

`asc::args::deferred::deferred`使用调用方提供的参数初始化`asc::args::deferred`对象。

## 函数原型

所属类型：[`asc::args::deferred`](args_deferred.md)。

### 原型1

```cpp
// asc::args::deferred 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr explicit deferred(const T* data, Bounds bounds) noexcept;
```

### 原型2

```cpp
// asc::args::deferred 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr explicit deferred(const T* data) noexcept;
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `data` | 输入 | 指向Device侧延迟数据的指针：值仅在流序到达后才可读；包装对象不复制数据，使用期间不得为空且所指存储须覆盖整个使用周期。 |
| `bounds` | 输入 | 该延迟参数取值的边界对象（no_bounds/static_bounds/runtime_bounds）：供后端无需同步读取Device数据即可做安全选择。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `data` | 输入 | 指向Device侧延迟数据的指针：值仅在流序到达后才可读；包装对象不复制数据，使用期间不得为空且所指存储须覆盖整个使用周期。 |

## 返回值说明

无返回值。

## 约束说明

- Bounds按值保存，可为no_bounds、static_bounds或runtime_bounds等可复制的边界值；包装不会自动证明或校验数据落在边界内。
- 延迟数据仅借用指针，须在实际读取时可访问且存储覆盖全部使用期；sequence的size以元素计并不得超过有效范围。

- 使用C++17，可在Host、AI Core SIMD编程 和AI Core SIMT编程中使用。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/argument>

bool example()
{
    int value = 7;
    asc::args::deferred<int> argument(&value, asc::args::no_bounds{});
    return argument.data() == &value && *argument.data() == 7;
}
```

## 关联API

- [`asc::args::deferred`](args_deferred.md)
- [本头文件的接口列表](asc_argument.md)
