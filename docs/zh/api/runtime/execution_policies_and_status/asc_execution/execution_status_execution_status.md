# asc::execution_status::execution_status

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

头文件路径为：`<asc/execution>`。

默认构造函数创建成功状态；带参构造函数创建指定状态，并且只在状态类别为 `backend_error` 时保留传入的原生状态码。

## 函数原型

### 原型 1

```cpp
constexpr asc::execution_status::execution_status() noexcept;
```

### 原型 2

```cpp
constexpr explicit asc::execution_status::execution_status(asc::execution_errc code, int native_code = 0) noexcept;
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `code` | 输入 | 要保存或查询的错误、执行状态类别。 |
| `native_code` | 输入 | 底层运行时返回的原生状态码；仅在对应错误类别下有意义。 |

## 约束说明

- 仅可在 Host 使用
- 状态值可平凡复制
- 成功状态的 code() 为 execution_errc::success，native_code() 为 0，失败状态保留可用于诊断的状态码

## 调用示例

以下 Host 片段使用具体对象演示调用；涉及资源操作时须遵守本页的初始化和生命周期约束。

```cpp
#include <asc/execution>

void example()
{
    asc::execution_status status{};
    (void)status.success();
}
```
