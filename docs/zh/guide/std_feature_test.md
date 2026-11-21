# 标准库特性修订检测

`<asc/std/version>` 报告 `asc::std` 的标准特性修订。标准名 `__cpp_lib_x` 一一映射为
`CANN_ASC_STL_LIB_x`，保留后缀大小写和标准规定的 `YYYYMML` 整数值。例如
`__cpp_lib_type_identity` 对应 `CANN_ASC_STL_LIB_type_identity == 201806L`。
这些是对象式宏，能用于预处理和版本阈值比较；未支持的特性不定义，不定义成 0。

`CANN_ASC_STL_HAS_*` 继续报告选定接口子集是否可用（0/1），不保证完整标准特性。
`CANN_ASC_STL_DETAIL_*` 是私有实现词汇，不是稳定接口。产品版本与扩展模块信息仍由
`<asc/version>` 负责，不使用产品发布日期作为标准特性的修订值。

定义描述当前翻译单元的语言、编译器内建和执行配置。除表中特别注明外，回移功能在
C++17/C++20 的 Host、AI Core SIMD/SIMT 中均可查询。Host 支持不推导 Device 支持。
当前支持编译器为 GCC、Clang 和 CANN BiSheng；表中的内建条件在实际编译器上检测。

## 已报告的修订

表中每个标准宏按上述规则映射为公开 ASC-STL 宏。值为已核对满足的最高修订；
同一行未报告的后续修订不会因较高语言模式而自动启用。

| 标准宏 | 报告值 | 对应功能头 | 修订要求与当前实现 | 定义条件 |
| --- | --- | --- | --- | --- |
| `__cpp_lib_addressof_constexpr` | `201603L` | `<asc/std/memory>` | constexpr 真地址，绕过重载 operator& | 有 __builtin_addressof（或 GCC 路径） |
| `__cpp_lib_apply` | `201603L` | `<asc/std/tuple>` | 按索引展开并调用 INVOKE；不报告 202506 的新增元编程入口 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_as_const` | `201510L` | `<asc/std/utility>` | 保留左值对象身份，拒绝 const 右值 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_bit_cast` | `201806L` | `<asc/std/bit>` | 等尺寸平凡复制类型、常量求值、非默认构造目标 | 有 constexpr bit_cast 内建；memcpy 回退时未定义 |
| `__cpp_lib_bitops` | `201907L` | `<asc/std/bit>` | 计数、旋转及零输入边界，限制无符号整数 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_bool_constant` | `201505L` | `<asc/std/type_traits>` | bool 常量的 integral_constant 别名 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_bounded_array_traits` | `201902L` | `<asc/std/type_traits>` | 有界和无界数组的类型及变量模板 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_byte` | `201603L` | `<asc/std/cstddef>` | byte 枚举、按位/移位操作及 to_integer | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_clamp` | `201603L` | `<asc/std/algorithm>` | 默认/自定义比较，返回选定实参的引用 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_constexpr_numeric` | `201911L` | `<asc/std/numeric>` | 累加、内积、归约、扫描、相邻差与 iota 的常量求值 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_endian` | `201907L` | `<asc/std/bit>` | little/big/native 枚举，依据当前目标字节序 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_exchange_function` | `201304L` | `<asc/std/utility>` | 移动旧值、赋新值并返回旧值 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_gcd_lcm` | `201606L` | `<asc/std/numeric>` | 混合整型、正负值、零及共同结果类型 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_has_unique_object_representations` | `201606L` | `<asc/std/type_traits>` | 完整对象表示判定及变量模板 | 编译器有 __has_unique_object_representations |
| `__cpp_lib_int_pow2` | `202002L` | `<asc/std/bit>` | has_single_bit/bit_ceil/bit_floor/bit_width，含零与边界 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_integer_comparison_functions` | `202002L` | `<asc/std/utility>` | 六种有符号/无符号安全比较及 in_range | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_integer_sequence` | `201304L` | `<asc/std/utility>` | 整型序列、索引序列及生成别名 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_integral_constant_callable` | `201304L` | `<asc/std/type_traits>` | 常量包装的 constexpr 调用运算符 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_invoke` | `201411L` | `<asc/std/functional>` | 普通函数、成员函数/数据成员，对象/指针/reference_wrapper | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_invoke_r` | `202106L` | `<asc/std/functional>` | 约束返回值转换、void 丢弃和 noexcept | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_is_aggregate` | `201703L` | `<asc/std/type_traits>` | 聚合判定及变量模板 | 编译器有 __is_aggregate |
| `__cpp_lib_is_constant_evaluated` | `201811L` | `<asc/std/type_traits>` | 区分 manifest 常量求值与运行期求值 | 有可靠 is_constant_evaluated 内建；否则未定义 |
| `__cpp_lib_is_final` | `201402L` | `<asc/std/type_traits>` | final 类判定及变量模板 | 编译器有 __is_final |
| `__cpp_lib_is_invocable` | `201703L` | `<asc/std/type_traits>` | INVOKE 结果、四种可调用/不抛判定和变量模板 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_is_nothrow_convertible` | `201806L` | `<asc/std/type_traits>` | 隐式转换的异常性，含 void 和不可转换输入 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_is_null_pointer` | `201309L` | `<asc/std/type_traits>` | nullptr_t（含 cv）判定 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_is_scoped_enum` | `202011L` | `<asc/std/type_traits>` | 限定枚举与非枚举的安全判定 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_is_swappable` | `201603L` | `<asc/std/type_traits>` | 双向 ADL swap、异常性、不可交换及 void 输入 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_launder` | `201606L` | `<asc/std/new>` | 编译器对象寿命/指针重建屏障 | 有 __builtin_launder（或 GCC 路径） |
| `__cpp_lib_logical_traits` | `201510L` | `<asc/std/type_traits>` | conjunction/disjunction/negation 和惰性短路 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_make_from_tuple` | `201606L` | `<asc/std/tuple>` | 按转发后的元素直接构造对象 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_make_reverse_iterator` | `201402L` | `<asc/std/iterator>` | 逆向迭代器工厂 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_not_fn` | `201603L` | `<asc/std/functional>` | 保存可调用对象、四种 cv/ref 调用及失败分支；不报告 202306 的无状态形式 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_raw_memory_algorithms` | `201606L` | `<asc/std/memory>` | 未初始化的移动/默认及值构造、销毁和异常回滚；不报告 202411 的 constexpr 修订 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_remove_cvref` | `201711L` | `<asc/std/type_traits>` | 移除引用及顶层 cv，保留数组形状 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_robust_nonmodifying_seq_ops` | `201304L` | `<asc/std/algorithm>` | equal/mismatch/is_permutation 的双范围重载 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_sample` | `201603L` | `<asc/std/algorithm>` | 输入/前向遍历分派及有界均匀采样 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_shift` | `201806L` | `<asc/std/algorithm>` | 经典 shift_left/right，前向及双向遍历；不报告 202202 的 ranges 重载 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_source_location` | `201907L` | `<asc/std/source_location>` | 立即求值的 current、默认/复制及四种观察器 | 仅 Host C++20 且有 consteval 和调用点内建；C++17/Device 未定义 |
| `__cpp_lib_ssize` | `201902L` | `<asc/std/iterator>` | 容器与内建数组的有符号长度 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_to_address` | `201711L` | `<asc/std/memory>` | 原始指针、pointer_traits 定制及递归 operator-> | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_to_array` | `201907L` | `<asc/std/array>` | 复制/移动内建数组，去 cv，拒绝多维数组 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_to_underlying` | `202102L` | `<asc/std/utility>` | 枚举到准确底层类型的 constexpr/noexcept 转换 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_tuple_element_t` | `201402L` | `<asc/std/tuple>` | tuple_element 的类型别名及 cv 传播 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_tuples_by_type` | `201304L` | `<asc/std/utility>`, `<asc/std/tuple>` | pair/tuple 按唯一元素类型取值，保留 cv/ref | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_type_identity` | `201806L` | `<asc/std/type_traits>` | 不推导上下文的类型包装及别名 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_unreachable` | `202202L` | `<asc/std/utility>` | noreturn、noexcept 的不可达标记 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_unwrap_ref` | `201811L` | `<asc/std/type_traits>` | reference_wrapper 解包及 decay 组合 | C++17/20；Host、SIMD、SIMT |
| `__cpp_lib_void_t` | `201411L` | `<asc/std/type_traits>` | 任意合法类型包映射到 void | C++17/20；Host、SIMD、SIMT |

## 保持未定义的特性

这些设施的已列子集仍可按原 API 文档使用；下表不授权删除或修订它们。没有对应标准宏的特殊适配能力只使用 HAS 查询。

| 标准宏后缀 | 标准修订值 | 当前缺口/未报告原因 |
| --- | --- | --- |
| `span` | 202002; 202311 | 静态 extent 的 iterator/count 及 dynamic→static span 转换缺少标准要求的 explicit；较新 at 也缺失 |
| `mdspan, submdspan` | 202207/202406; 202306/202411 | C++17/20 使用 operator()；标准多参数 operator[] 依赖原生语言支持，切片/布局也是选定子集 |
| `expected` | 202202; 202211 | 没有 bad_expected_access 异常接口；不能由已提供的 monadic 方法推导完整支持 |
| `optional` | 201606; 202106; 202110; 202506 | 缺少 `value()` 检查访问接口及 `bad_optional_access` 异常类型 |
| `variant` | 201606; 202102; 202106 | 没有 bad_variant_access，错误访问采用 trap |
| `inplace_vector` | 202406 | 提供固定容量子集，insert/完整异常协议等标准入口未齐 |
| `allocate_at_least` | 202302 | 提供自由函数回移；缺少 allocator_traits::allocate_at_least 标准成员及标准 allocator |
| `format` | 201907 及后续 | format_to 等选定格式化能力未覆盖 format/wformat、locale 和全部 formatter 协议 |
| `ranges` | 201911 及后续 | 视图和部分 ranges 算法不是完整的 ranges 算法/协议集合 |
| `philox_engine` | 202406 | 缺少 SeedSequence 构造/seed 和流读写等引擎要求 |
| `math_constants` | 201907 | 变量模板仅有 float 特化，缺少 double/long double |
| `concepts` | 202002; 202207 | C++17 是布尔判定；C++20 same_as 未保证对称约束的标准 subsumption |
| `forward_like` | 202207 | 目前复制 T 的 volatile，标准仅合并其 const 和引用类别 |
| `byteswap` | 202110 | 当前明确排除 bool，与标准 integral 参与集合不同 |
| `array_constexpr` | 201603; 201811 | array 缺少 at 等完整成员，不能仅由 constexpr 遍历宣称完整修订 |
| `nonmember_container_access` | 201411 | empty/data 缺少 initializer_list 重载 |
| `transformation_trait_aliases, type_trait_variable_templates` | 201304; 201510 | C++17 缺少 result_of_t、is_literal_type_v 等家族成员 |
| `destroying_delete` | 201806 | 只有本库 tag，不能启用编译器针对 std::destroying_delete_t 的语言机制 |
| `allocator_traits_is_always_equal` | 201411 | 显式分配器及容器传播/异常约束为当前子集；vector 移动赋值无条件 noexcept |
| `scoped_lock, shared_mutex, shared_timed_mutex` | 201703; 201505; 201402 | 非抛锁子集及锁包装；scoped_lock 的 try_lock 异常路径终止，缺少完整标准互斥量类型 |
| `atomic_*, barrier, latch, semaphore` | 各宏的标准修订 | 执行位置/类型/等待与调度要求各有适配子集；本次不提升为标准完整支持 |
| `execution, parallel_algorithm` | 201603/201902; 201603 | 执行策略词汇不表示全部标准并行算法重载已实现 |
| `chrono, string_view, to_chars 及其他家族` | 各宏的标准修订 | chrono 为受限时钟/日历；字符串为受限字符/分配器接口；字符转换、关联容器及其他宏未完成整体修订核对，保持未定义 |

## 来源和维护

本表固定使用 [N4861（C++20）§17.3.2](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/n4861.pdf)、
[N4950（C++23）§17.3.2](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/n4950.pdf) 和
[N5014（2025-08 C++26 草案）§17.3.2](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2025/n5014.pdf)
的 `[version.syn]` 及相应组件条款。后续更新先核对新修订的全部要求，再同步定义、表和测试。
特别是 `not_fn` 的 202306、`shift` 的 202202 和原始内存算法的 202411，不由旧修订自动推出。

定义集中维护，`<asc/std/version>` 和对应功能头共用。ASC-STL 不转引宿主 `<version>` 的值，
也不定义任何宿主 `__cpp_lib_*`；两套名字可在任意包含顺序下同时使用。
旧开关 `CANN_ASC_STL_ENABLE_LEGACY_STD_FEATURE_MACROS` 现在不产生作用；旧代码改为
`CANN_ASC_STL_LIB_source_location`/`CANN_ASC_STL_LIB_unreachable`，或继续用 HAS 查询子集。

验证覆盖双语言的独立/重复/交叉包含、宿主宏快照、内建不足和新旧阈值分支，并通过
公开功能头独立调用关键接口。`source_location::current` 的 Host C++20 入口为 consteval；
C++17/Device 保留原 constexpr 子集，不能据此取得标准版本宏。Device 编译结果不表示真机运行验收。

共存测试逐头探测当前编译器可包含的宿主头，仅将缺少的宿主组合记为 `NOT_APPLICABLE`。
ASC 自身的修订值、门控、宏隔离和接口检查始终执行；存在但预处理失败的宿主头仍使测试失败。
