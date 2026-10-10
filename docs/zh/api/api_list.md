# ASC-STL API 列表

按功能分类查找 ASC-STL 接口。各分类页面列出可用头文件、接口及支持范围。当前版本支持 Ascend 950 系列；其他列出的产品系列不支持。

## API 分类总览

| 一级分类 | 二级分类 | 能力说明 |
| --- | --- | --- |
| [C++ 标准库接口](standard/standard.md) | [语言支持库](standard/language_support/language_support.md) | 基础类型、特性宏、源码位置与语言设施。 |
| [C++ 标准库接口](standard/standard.md) | [概念库](standard/concepts/concepts.md) | 用于表达模板参数要求的标准概念。 |
| [C++ 标准库接口](standard/standard.md) | [诊断库](standard/diagnostics/diagnostics.md) | 断言、错误码与诊断相关接口。 |
| [C++ 标准库接口](standard/standard.md) | [内存管理库](standard/memory_management/memory_management.md) | 对象生命周期、分配器与内存操作。 |
| [C++ 标准库接口](standard/standard.md) | [元编程库](standard/metaprogramming/metaprogramming.md) | 类型特征、编译期计算与模板辅助设施。 |
| [C++ 标准库接口](standard/standard.md) | [通用工具库](standard/utilities/utilities.md) | 通用对象、函数对象与值操作工具。 |
| [C++ 标准库接口](standard/standard.md) | [容器库](standard/containers/containers.md) | 序列、关联容器及其适配器。 |
| [C++ 标准库接口](standard/standard.md) | [迭代器库](standard/iterators/iterators.md) | 迭代器、哨兵和迭代器适配器。 |
| [C++ 标准库接口](standard/standard.md) | [范围库](standard/ranges/ranges.md) | 范围视图、范围访问及范围适配器。 |
| [C++ 标准库接口](standard/standard.md) | [算法库](standard/algorithms/algorithms.md) | 查找、排序、变换和数值算法。 |
| [C++ 标准库接口](standard/standard.md) | [字符串库](standard/strings/strings.md) | 字符序列、字符串视图与字符串操作。 |
| [C++ 标准库接口](standard/standard.md) | [文本处理库](standard/text_processing/text_processing.md) | 字符分类、转换和文本格式处理。 |
| [C++ 标准库接口](standard/standard.md) | [数值库](standard/numerics/numerics.md) | 数学函数、复数、随机数及数值运算。 |
| [C++ 标准库接口](standard/standard.md) | [日期和时间库](standard/chrono/chrono.md) | 时钟、时间段、日历与时间转换。 |
| [C++ 标准库接口](standard/standard.md) | [输入/输出库](standard/input_output/input_output.md) | 输入输出相关的类型与工具。 |
| [C++ 标准库接口](standard/standard.md) | [并发支持库](standard/concurrency/concurrency.md) | 原子、同步和并发操作设施。 |
| [昇腾扩展接口](extension/extension.md) | [设备原子操作与线程同步](extension/device_atomics_and_sync/device_atomics_and_sync.md) | 设备端原子操作、屏障与线程同步。 |
| [昇腾扩展接口](extension/extension.md) | [异步数据搬运流水线](extension/async_data_pipeline/async_data_pipeline.md) | 异步搬运及其完成状态管理。 |
| [昇腾扩展接口](extension/extension.md) | [地址空间与内存视图](extension/address_spaces_and_memory_views/address_spaces_and_memory_views.md) | 设备内存地址空间、非拥有视图与分配工具。 |
| [昇腾扩展接口](extension/extension.md) | [多维数据视图与搬运](extension/multidimensional_views_and_transfer/multidimensional_views_and_transfer.md) | 多维索引、数据视图和张量搬运。 |
| [昇腾扩展接口](extension/extension.md) | [设备执行层次、集体操作与动态任务获取](extension/execution_hierarchy_and_collectives/execution_hierarchy_and_collectives.md) | 线程层次查询、集体操作与工作领取。 |
| [昇腾扩展接口](extension/extension.md) | [设备端并行算法与参数包装](extension/device_parallel_algorithms_and_arguments/device_parallel_algorithms_and_arguments.md) | 异步并行算法及其执行参数。 |
| [昇腾扩展接口](extension/extension.md) | [算法函数对象、操作属性与迭代器适配器](extension/function_objects_and_iterators/function_objects_and_iterators.md) | 算法调用对象、操作属性和迭代器适配器。 |
| [昇腾扩展接口](extension/extension.md) | [位操作、数学与数值计算、伪随机数](extension/bit_math_numeric_random/bit_math_numeric_random.md) | 位运算、数学工具、数值运算和随机数。 |
| [昇腾扩展接口](extension/extension.md) | [类型特征、通用工具与版本检测](extension/type_traits_and_utilities/type_traits_and_utilities.md) | 扩展类型特征、通用工具及版本检测。 |
| [运行时接口](runtime/runtime.md) | [设备、Stream与Event管理](runtime/devices_streams_events/devices_streams_events.md) | 设备查询、Stream 和 Event 生命周期管理。 |
| [运行时接口](runtime/runtime.md) | [核函数调用](runtime/kernel_launch/kernel_launch.md) | 从 Host 提交设备核函数。 |
| [运行时接口](runtime/runtime.md) | [设备端执行策略、执行要求与提交状态](runtime/execution_policies_and_status/execution_policies_and_status.md) | 执行策略、运行要求与异步提交状态。 |
| [运行时接口](runtime/runtime.md) | [内存资源、内存池与缓冲区](runtime/memory_resources_and_buffers/memory_resources_and_buffers.md) | 设备内存资源、内存池及拥有式缓冲区。 |

## 调用接口依赖的头文件

| 接口类别 | 头文件形式 | 说明 |
| --- | --- | --- |
| C++ 标准库接口 | `<asc/std/...>` | 使用 `asc::std` 命名空间中的标准库接口。 |
| 昇腾扩展接口 | `<asc/...>` | 使用 `asc` 命名空间中的 Device 与并行扩展。 |
| 运行时接口 | `<asc/...>` | 在 Host 侧管理设备资源并提交异步工作。 |
