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

`asc::args::deferred::deferred` 使用调用方提供的参数初始化 `asc::args::deferred` 对象。

## 函数原型

### 原型 1

```cpp
constexpr asc::args::deferred::deferred(const T* data, Bounds bounds) noexcept;
```

### 原型 2

```cpp
constexpr explicit asc::args::deferred::deferred(const T* data) noexcept;
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `data` | 输入 | 指向 Device 侧延迟数据的指针：值仅在流序到达后才可读；包装对象不复制数据，使用期间不得为空且所指存储须覆盖整个使用周期。 |
| `bounds` | 输入 | 该延迟参数取值的边界对象（no_bounds/static_bounds/runtime_bounds）：供后端无需同步读取 Device 数据即可做安全选择。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `data` | 输入 | 指向 Device 侧延迟数据的指针：值仅在流序到达后才可读；包装对象不复制数据，使用期间不得为空且所指存储须覆盖整个使用周期。 |

## 约束说明

- 使用 C++17，可在 Host、AI Core SIMD 编程 和 AI Core SIMT 编程中使用
- Bounds 必须为 asc::args::no_bounds 或 asc::args::static_bounds
- 延迟指针在使用时不得为空，调用方存储必须覆盖整个使用周期

## 调用示例

以下 Host 片段使用具体类型演示本页接口；对象和指针的有效期须满足本页约束。

```cpp
#include <asc/argument>

void example(const int* values)
{
    // values 在使用 deferred 的整个期间保持有效。
    asc::args::deferred<int> argument(values, asc::args::no_bounds{});
    (void)argument.data();
}
```
