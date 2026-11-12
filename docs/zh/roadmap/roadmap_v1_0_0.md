# ASC-STL v1.0.0 支持范围说明

> **当前代码版本**：1.0.0 · **正式发布时间**：待公布。
>
> [README](../../../README.md) · [标准层 API 支持列表](../api/standard/standard.md)

## 当前定位

当前 `master` 提供标准层已实现的功能，涵盖 16 类、74 个公共头，统一以 `<asc/std/...>` 包含，并使用 `asc::std` 命名空间。昇腾扩展层与 Runtime 层正在持续完善。

## 标准层已有功能

下表列出标准层公共头及功能，详细接口见对应 API 文档。

| 现有分类 | 公共头 | 当前可使用的功能范围 |
| --- | --- | --- |
| [语言支持库](../api/standard/language_support/language_support.md) | `cfloat` `climits` `cstddef` `cstdint` `exception` `compare` `new` `limits` `source_location` `version` `ciso646` `cstdalign` `cstdbool` | 基础类型与数值宏、比较类别、源码位置、能力检测，以及终止和 placement new 等已列出的语言支持接口。 |
| [概念库](../api/standard/concepts/concepts.md) | `concepts` | 类型与表达式判定；C++17 提供布尔变量模板，C++20 可使用原生 concept。 |
| [诊断库](../api/standard/diagnostics/diagnostics.md) | `cassert` `cerrno` `system_error` | 断言、错误码宏，以及 error_code、error_condition 和错误类别。 |
| [内存管理库](../api/standard/memory_management/memory_management.md) | `memory` `scoped_allocator` | 指针与分配器特征、分配器协议、对象构造/销毁及未初始化内存算法。 |
| [元编程库](../api/standard/metaprogramming/metaprogramming.md) | `type_traits` `ratio` | 类型查询、类型变换、编译期常量与有理数运算。 |
| [通用工具库](../api/standard/utilities/utilities.md) | `utility` `functional` `tuple` `optional` `variant` `expected` `bit` `bitset` `cstdlib` | 移动/转发/交换、函数对象、值组合与可选值、结果与错误表示、位操作和位集合等工具。 |
| [容器库](../api/standard/containers/containers.md) | `array` `vector` `deque` `list` `forward_list` `inplace_vector` `map` `set` `unordered_map` `unordered_set` `queue` `stack` `span` `mdspan` | 固定容量与动态容器、关联容器、适配器及连续/多维视图，动态容器使用显式分配器。 |
| [迭代器库](../api/standard/iterators/iterators.md) | `iterator` | 迭代器属性、遍历辅助、插入/逆向/移动等迭代器适配。 |
| [范围库](../api/standard/ranges/ranges.md) | `ranges` | 范围访问与判定、范围视图及过滤、变换、截取等视图组合。 |
| [算法库](../api/standard/algorithms/algorithms.md) | `algorithm` `execution` | 遍历、查找、比较、复制、变换、分区、排序、二分、集合、堆与排列等算法，以及执行策略词汇。 |
| [字符串库](../api/standard/strings/strings.md) | `cstring` `string` `string_view` | C 字符串/字节操作、显式分配器 basic_string、字符特征及字符串视图。 |
| [文本处理库](../api/standard/text_processing/text_processing.md) | `cctype` `charconv` `cuchar` `cwchar` `cwctype` `format` | 字符分类、字符/数值转换、宽字符与多字节处理，以及 format_to 等格式化输出接口。 |
| [数值库](../api/standard/numerics/numerics.md) | `cmath` `complex` `ccomplex` `ctgmath` `numbers` `linalg` `random` `numeric` | 标量数学、复数、数学常量、随机引擎/分布、数值算法；linalg 当前提供缩放、共轭、转置等视图适配。 |
| [日期和时间库](../api/standard/chrono/chrono.md) | `chrono` `ctime` | 时间段、时间点、日历与转换；计时与时间转换。 |
| [输入/输出库](../api/standard/input_output/input_output.md) | `cinttypes` | 定宽整数格式宏与 intmax_t 相关工具。 |
| [并发支持库](../api/standard/concurrency/concurrency.md) | `atomic` `barrier` `latch` `semaphore` `mutex` `shared_mutex` | 原子、屏障、倒计数和信号量，以及 RAII 锁管理。 |

## 扩展层与 Runtime 层

| 接口层 | 当前方向 | API 文档 |
| --- | --- | --- |
| 昇腾扩展层（现有 9 类） | 继续完善设备原子/同步、地址空间与视图、搬运流水线、执行层次与协作、设备算法及配套数值工具 | [扩展 API](../api/extension/extension.md) |
| Runtime 层（现有 4 类） | 继续完善设备、Stream/Event、核函数提交、执行要求、内存资源和异步回收 | [Runtime API](../api/runtime/runtime.md) |

## 标准层特性检测更新

新增 `CANN_ASC_STL_LIB_*` 标准修订检测，保留 HAS 子集查询，停止旧兼容开关对宿主宏的注入。
Host C++20 的 `source_location::current` 改为立即函数，`unreachable` 补充 noexcept，
`<asc/std/type_traits>` 补齐 unwrap_reference 系列的公开入口。详见[特性清单](../guide/std_feature_test.md)。
