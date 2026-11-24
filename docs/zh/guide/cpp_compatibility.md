# 语言模式与兼容性

ASC-STL最低使用C++17，并维护C++17和C++20两种语言模式。接口纳入ISO标准的年份、编译器版本、Host标准库版本和CANN版本分别描述不同条件。选择C++17不会阻止使用本库已经回移的较新库接口；具体重载与执行位置以API页面为准。

## 类型与表达式判定

`<asc/std/concepts>`、`<asc/std/iterator>`和`<asc/std/ranges>`中的公开判定名字在C++17中提供同名`inline constexpr bool`变量模板，在支持concept的C++20及以上配置中提供concept，实际形式可通过`CANN_ASC_STL_HAS_NATIVE_CONCEPTS`查询。`static_assert(asc::std::integral<int>)`可在两种模式使用；C++17还可用布尔结果控制`enable_if`。

受约束模板参数、`requires`语法、concept约束偏序、`char8_t`、三路比较语法和多参数下标需要相应语言及编译器能力。C++17中的同名布尔判定不会提供这些语言机制。

## 接口、执行位置与常量求值

下列信息须分别检查：

- **语言模式**决定声明和调用语法是否可表达。`to_array`、span连续range构造、已选expected、inplace_vector和Philox等库设施有C++17实现；较新标准来源不等于较高最低语言要求。
- **执行位置**决定接口能否在Host、AI Core SIMD或AI Core SIMT调用。Host的系统库、CANN Runtime和设备地址空间条件仍独立存在。Host字符转换须由系统`<cuchar>`真实提供所需接口，单独更换语言选项不能补齐系统库能力。
- **常量求值**还要求整个表达式、对象生命周期和元素操作满足该语言模式的规则。普通运行调用可用，不代表同一操作能用于`static_assert`；`constexpr`声明也不保证任意模板实参都能常量求值。

`format_to_n_result`结果聚合在C++17可用。内部渲染实现可在C++17复用，这不增加公开的运行时格式化接口；带类型格式化调用仍需要C++20和`consteval`立即校验。`destroying_delete_t`及其对象在C++17仅作为普通标签词汇提供，不启用编译器销毁型delete机制。`cstdalign`和`cstdbool`的两个C兼容功能宏仅在C++17由本库补充。

C++17与C++20还可能保留不同年代的类型规则，例如`common_type`的部分回退和插入迭代器的`difference_type`。部分对象在C++20使用`no_unique_address`压缩成员布局；跨翻译单元传递此类对象时应使用一致的语言模式与配置。

范围视图的缓存与存储语义补齐会改变部分具体view类型的对象布局。更新这些实现后，所有依赖组件需要重新编译，并在相关翻译单元中使用一致的语言模式与配置。保持按语言选择属性的原有策略，也不表示具体类型具有字节级ABI稳定性。

本库提供的较新接口按各自子集说明维护。C++23或C++26来源接口的存在，不构成对相应完整语言模式或完整标准库的支持声明。

## 查询ASC-STL能力

包含`<asc/std/version>`后，使用`CANN_ASC_STL_HAS_*`对象式宏查询本库能力。所有查询宏均有定义，其值为0或1；值为1仍须遵守具体API的重载、类型和执行位置约束。这些宏描述ASC-STL的已选接口子集，不表示整个ISO标准版本已完整实现，也不表示Host的`std`提供同名设施。

| 宏 | 查询内容 |
| --- | --- |
| `CANN_ASC_STL_HAS_SOURCE_LOCATION` | source_location位置词汇 |
| `CANN_ASC_STL_HAS_UNREACHABLE` | unreachable不可达标记 |
| `CANN_ASC_STL_HAS_TYPE_IDENTITY` | type_identity类型工具 |
| `CANN_ASC_STL_HAS_ENDIAN` | endian字节序词汇 |
| `CANN_ASC_STL_HAS_IS_CONSTANT_EVALUATED` | 可靠区分常量求值与运行期求值的编译器能力 |
| `CANN_ASC_STL_HAS_CONCEPT_PREDICATES` | 类型、迭代器与范围的布尔判定形式 |
| `CANN_ASC_STL_HAS_NATIVE_CONCEPTS` | 当前语言模式中的原生concept形式 |
| `CANN_ASC_STL_HAS_SPAN` | span已列出的连续视图接口 |
| `CANN_ASC_STL_HAS_TO_ARRAY` | to_array左值与右值数组重载 |
| `CANN_ASC_STL_HAS_MDSPAN` | mdspan已列出的多维视图接口 |
| `CANN_ASC_STL_HAS_SUBMDSPAN` | submdspan已列出的切片接口 |
| `CANN_ASC_STL_HAS_EXPECTED` | expected已列出的非抛出接口 |
| `CANN_ASC_STL_HAS_OPTIONAL_REFERENCE` | optional<T&>已列出的引用接口 |
| `CANN_ASC_STL_HAS_INPLACE_VECTOR` | inplace_vector已列出的非抛出接口 |
| `CANN_ASC_STL_HAS_PHILOX` | Philox计数式随机引擎 |
| `CANN_ASC_STL_HAS_ALLOCATE_AT_LEAST` | allocate_at_least成员检测与回退分派 |
| `CANN_ASC_STL_HAS_FORMAT_TO_N_RESULT` | format_to_n_result结果聚合 |
| `CANN_ASC_STL_HAS_FORMAT` | 带类型格式化的consteval校验接口 |

`CANN_ASC_STL_HAS_CONCEPT_PREDICATES`与`CANN_ASC_STL_HAS_NATIVE_CONCEPTS`分别表示布尔判定词汇和原生concept能力。`CANN_ASC_STL_HAS_FORMAT`同时检查所需的立即函数能力；`CANN_ASC_STL_HAS_IS_CONSTANT_EVALUATED`表示编译器能够可靠区分常量求值。

以下Host示例按ASC能力宏选择调用。

```cpp
#include <asc/std/version>
#include <asc/std/array>

#if CANN_ASC_STL_HAS_TO_ARRAY
constexpr int input[2] = {2, 4};
constexpr auto values = asc::std::to_array(input);
static_assert(values[1] == 4);
#endif
```

## 标准特性版本与旧宏迁移

完整标准特性用 `CANN_ASC_STL_LIB_x >= YYYYMML` 查询；不完整特性不定义版本宏。
名称映射、版本与支持边界见[特性清单](std_feature_test.md)。HAS 仍用于已列接口子集。

```cpp
#include <asc/std/version>
#include <asc/std/array>

#if defined(CANN_ASC_STL_LIB_to_array) && CANN_ASC_STL_LIB_to_array >= 201907L
constexpr auto values = asc::std::to_array({2, 4});
static_assert(values[1] == 4);
#endif
```

旧的 `CANN_ASC_STL_ENABLE_LEGACY_STD_FEATURE_MACROS` 开关现在不产生作用。
把本库的旧标准名判断迁移到 `CANN_ASC_STL_LIB_source_location`、
`CANN_ASC_STL_LIB_unreachable`，或用 HAS 查询原有子集。宿主 `__cpp_lib_*` 仅描述宿主 std。

`source_location::current` 在支持立即函数的 Host C++20 中为 consteval，显式实参也须满足
常量表达式要求；其 C++17/Device constexpr 子集保持。`unreachable` 明确为 noexcept。

## Host编译器能力

重复键查找、复数频响和带padding的张量视图使用路径已在GCC 9.5与GCC 13的C++17模式验证；这不代表所有头文件在所有GCC版本均受支持。这些依赖中的类型相等判定使用ASC-STL类型特征，不要求较新的`__is_same`内建函数。编译器没有内建函数能力检测时，平凡析构判定使用GCC已有的`__has_trivial_destructor`。
GCC 9.5 的 Host C++17 代码可以包含 `<asc/std/algorithm>`，并对 `asc::std::set` 和 `asc::std::map` 的迭代器使用 `ranges::find`。该头文件包含的作用域原子声明使用 `asc::std::is_same_v` 检查四种受支持的整数类型。

缺少`__builtin_bit_cast`时，浮点编解码仍可在运行期调用，但需要该操作的转换不能常量求值。要求constexpr位转换前，应检查是否定义`CANN_ASC_STL_LIB_bit_cast`。pair-like构造约束先排除非tuple-like来源，再尝试访问元素，因此切片内部使用的引用tuple也能正常构造。

`ranges::iter_swap`的自定义交换查找支持GCC 9/11的Host模式。迭代器可通过隐藏友元或关联命名空间中的二参数`iter_swap`定制交换；即使解引用返回只读引用，只要自定义交换有效，也不应退化为不可交换。没有适用的自定义函数时，仍按元素交换或移动交换路径判断可用性。

## C++17/C++20 仿真回归

`bash scripts/ci-cannsim-check.sh` 分别以 Release 模式构建、运行 C++17 和 C++20 测试。范围算法将八种输入长度分配到独立的数据切片，由一次启动的八个 block 完成；每种长度仍检查 GM/UB 两条路径的全部结果。W13/W14 SIMT 将六组独立的单线程检查分配到一次启动的六个 block，完成后再汇总结果并单独执行四线程同步检查，以减少重复仿真调度。

`ASC_STL_CANNSIM_CASE_TIMEOUT_SECONDS` 设置仿真回归用例的基础时限，默认为 600 秒。`runtime.cannsim.numeric-types.simt` 使用基础时限的 1.5 倍，默认 900 秒。超时计为失败。
比较回归耗时应使用相同模拟器、工具链和运行资源，并在目标 CI 环境确认运行结果。
