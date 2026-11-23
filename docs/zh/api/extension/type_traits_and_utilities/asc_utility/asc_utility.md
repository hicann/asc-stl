# 头文件asc/utility

提供按常量索引执行的 `static_for` 和同类型数值闭区间检查 `in_range`。回调可在运行时执行。

## 使用方式

```cpp
#include <asc/utility>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::in_range](in_range.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::static_for](static_for.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |

## 行为调整

函数对象改为引用借用，索引使用标准 `integral_constant`，并明确支持的数值类型。原来依赖回调复制、仅有 `operator() &&` 或对用户类型直接调用 `in_range` 的代码需要相应调整。详细规则见各 API 页面。
