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

## 迁移旧的特性宏判断

默认情况下，ASC-STL不再为自身设施补充`__cpp_lib_source_location`或`__cpp_lib_unreachable`。Host标准库已经定义的宏保持原样。查询ASC接口的旧代码应改用`CANN_ASC_STL_HAS_SOURCE_LOCATION`和`CANN_ASC_STL_HAS_UNREACHABLE`；查询Host `std`时继续使用Host自己的特性宏。

确需过渡时，可在任何ASC头文件之前显式启用兼容开关：

```cpp
#define CANN_ASC_STL_ENABLE_LEGACY_STD_FEATURE_MACROS 1
#include <asc/std/version>
```

此开关仅在标准名宏尚未定义时补充旧值，供旧的ASC能力判断迁移使用。开启后，这两个名字仍不能证明Host `std`具有对应设施。完成迁移后可移除兼容开关。
