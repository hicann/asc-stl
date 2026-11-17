# `<asc/numeric_types>`：低精度数值格式

头文件提供低精度数据的存储、编码访问、原生值桥接和显式标量转换。最低 C++17，同时支持 C++20。
纯 Host 包含无需 CANN SDK。独立包装是类类型，标准层的 integral、floating_point 和 arithmetic 分类为 false。

## 产品支持情况

Host：无 SDK；Device：BiSheng 15、dav-3510，严格浮点配置。

## 功能说明

低精度存储、编码访问、原生桥接和显式转换。

## 类型与表示

| 类型 | 编码 | 大小/对齐 | 元素数 |
| --- | --- | --- | --- |
| `asc::float16` | binary16，1/5/10，bias 15 | 2/2 | 1 |
| `asc::bfloat16` | BF16，1/8/7，bias 127 | 2/2 | 1 |
| `asc::float8_e4m3fn` | E4M3FN，最大有限值 448，NaN，无 Inf | 1/1 | 1 |
| `asc::float8_e5m2` | E5M2，最大有限值 57344，Inf/NaN | 1/1 | 1 |
| `asc::float8_e8m0` | 无符号缩放编码：0..254 为 2^(code-127)，255 为 NaN | 1/1 | 1 |
| `asc::hifloat8` | Ascend HiFloat8，D 域选择指数/尾数分配 | 1/1 | 1 |
| `asc::float4_e2m1x2` | 两个 E2M1 编码，正幅值 0、0.5、1、1.5、2、3、4、6 | 1/1 | 2 |
| `asc::float4_e1m2x2` | 两个 E1M2 编码，正幅值 0、0.25、0.5、0.75、1、1.25、1.5、1.75 | 1/1 | 2 |
| `asc::int4` | 四位二补码 [-8,7]，高四位为 0 | 1/1 | 1 |
| `asc::int4x2` | 两个四位二补码编码 | 1/1 | 2 |

各类型具有标准布局，默认构造、复制/移动构造、赋值和析构保持平凡。值初始化 `T{}` 得到全 0 编码；
E8M0 的该编码表示 2^-127。普通局部变量 `T x;` 须先写后读。复制和赋值保持编码。
数值初始化通过 `numeric_convert` 显式完成；这些包装提供存储和转换能力，算术与比较由调用方在转换后执行。
`int4` 数组的每个元素占一字节，紧凑存储使用 `int4x2`。

SIMT 使用普通指针读写包装数组。SIMD 的 GM/UB 对象按平凡复制表示搬运至本地标量对象，
再调用位访问或转换接口；带地址空间限定的类对象读写采用对应编译器/SDK 的搬运方式。

## 格式登记与位接口

以下声明均位于 `namespace asc`，整数类型为 `asc::std` 的对应定宽类型。

```cpp
enum class numeric_format {
    fp16 = 0, bf16 = 1, fp8_e4m3fn = 2, fp8_e5m2 = 3, fp8_e8m0 = 4,
    hif8 = 5, fp4_e2m1x2 = 6, fp4_e1m2x2 = 7, int4x2 = 8, int4 = 9
};
template<class T> struct numeric_format_traits;
template<class T>
constexpr typename numeric_format_traits<T>::storage_type to_bits(T value) noexcept;
template<class T>
constexpr T from_bits(typename numeric_format_traits<T>::storage_type bits) noexcept;
template<class Packed> constexpr Packed pack_elements(uint8_t low, uint8_t high) noexcept;
template<class Packed> constexpr uint8_t unpack_element(Packed value, unsigned index) noexcept;
```

`numeric_format_traits<T>` 接受表中十种无 cv/ref 类型，成员为 `storage_type`、`format`、`bits`、
`storage_bits`、`lanes`、`has_native_type`；映射可用时还有 `native_type`。
`bits` 为每元素位数；完整存储位数为 `storage_bits`；元素数为 `lanes`。FP16/BF16 的 storage_type 为
uint16_t，其余为 uint8_t。traits 只描述格式，转换支持另行查询。

位接口保留全部合法编码，包括 NaN 的符号与 payload。`int4` 的输入编码仅允许 0..15。
两种 FP4x2 与 int4x2 支持打包：low/high 各为 0..15，依次写入低/高四位；索引 0/1 返回零扩展编码。
非法编码、四位输入或索引在常量求值时编译失败，运行时进入 `asc::std::terminate`。
宽整数输入须在转换为参数类型前检查范围。两字节对象的内存端序跟随平台 ABI；to_bits 返回整数编码。

## 原生值互操作

```cpp
template<class T> using native_numeric_t = typename numeric_format_traits<T>::native_type;
template<class T> native_numeric_t<T> to_native_numeric(T value) noexcept;
template<class T> T from_native_numeric(const native_numeric_t<T>& value) noexcept;
```

首批适配 CANN 9.2.0-beta.2、BiSheng 15、dav-3510 的 Device 编译上下文。
FP16/BF16 映射 half/bfloat16_t；三种 FP8、HiFloat8、两种 FP4x2 分别映射同格式的 SDK 内置类型。
SIMD 还提供 int4x2_t 映射；int4 无原生映射。纯 Host 及其他上下文的 `has_native_type` 为 false，
无 native_type，桥接表达式替换失败。桥接逐位保留编码；SDK 的平凡可复制 int4x2_t 按位桥接；旧版非平凡包装通过已核对的公开字节适配。
对象桥接保持值表示；包装指针与原生指针的互相别名需要调用方另行遵守对象与地址空间规则。

## 显式标量转换

```cpp
enum class rounding_mode { nearest_even = 0, toward_zero = 1, toward_positive = 2, toward_negative = 3 };
enum class saturation_mode { none = 0, finite = 1 };
template<class To, rounding_mode R = rounding_mode::nearest_even,
         saturation_mode S = saturation_mode::none, class From>
To numeric_convert(From value) noexcept;
template<class To, class From, rounding_mode R = rounding_mode::nearest_even,
         saturation_mode S = saturation_mode::none>
inline constexpr bool is_numeric_conversion_supported_v = /* configured support matrix */;
```

To/From 为无 cv/ref 值类型。接口重载与支持查询使用同一支持表；查询 false 的组合不可调用。
下表的四种浮点为 float16、bfloat16、float8_e4m3fn、float8_e5m2。

| 源 | 目标 | R | S |
| --- | --- | --- | --- |
| float | 四种浮点 | 四种模式 | none/finite |
| 四种浮点 | float | 四种模式 | none/finite |
| int32_t | int4 | 四种模式，结果相同 | finite，钳到 [-8,7] |
| int4 | int32_t | 四种模式，结果相同 | none/finite，符号扩展 |

其他组合查询 false，包括扩展类型间、相同类型、double、E8M0、HiFloat8、打包类型及普通整数间转换。
Host 浮点路径要求 IEEE binary32 float；Device 软件路径首批面向 BiSheng 15、dav-3510 的 SIMT/SIMD
标量上下文。浮点路径要求严格配置，`-ffast-math` 下查询 false。未知枚举值和其他 Device 目标也查询 false。

有限值先在目标精度、渐进下溢的模型中按 R 舍入，再判断范围。nearest_even 的中点选择最低有效位为偶数的邻值。
none 的范围溢出：支持 Inf 的格式按方向产生带符号 Inf 或最大有限值，E4M3FN 产生规范 NaN。
finite 将溢出和源 Inf 按符号钳到目标最大有限值。none 保留支持 Inf 格式的源 Inf；向 E4M3FN 转入 Inf 得到 NaN。
符号零保持，下溢产生次正规数或带源符号的零。NaN 在两种饱和选项下均规范化，丢弃源符号/payload。
规范 NaN 为 FP16 0x7e00、BF16 0x7fc0、E4M3FN 0x7f、E5M2 0x7e、float 0x7fc00000。
转换使用整数位运算，不读取或修改舍入、饱和或 FTZ 状态，不承诺浮点异常标志。

## 约束说明

调用须满足各节的格式、索引、转换和编译配置条件。

## 调用示例

```cpp
#include <asc/numeric_types>

int main()
{
    const auto stored = asc::numeric_convert<asc::float16>(1.5f);
    const float value = asc::numeric_convert<float>(stored);
    const auto packed = asc::pack_elements<asc::int4x2>(0x8, 0x7);
    const auto low = asc::from_bits<asc::int4>(asc::unpack_element(packed, 0));
    const auto signed_low = asc::numeric_convert<asc::std::int32_t>(low);
    return value == 1.5f && asc::to_bits(stored) == 0x3e00 && signed_low == -8 ? 0 : 1;
}
```

## 模块与交付

numeric_types 的私有存储定义同时供 type_traits 读取；标准层的对象性质查询保持类类型语义。
通用 trait 仍由 type_traits 维护；普通整数检查转换由 numeric 维护。
`CANN_ASC_STL_HAS_NUMERIC_TYPES` 只在 version 的产品信息根定义，统一表示 Issue #85 的完整最小集合与适用验收。
原生加速、其他芯片和后续格式转换按各自支持条件开放。当前交付状态以该宏及 PR 验证说明为准。

设计：[Issue #85](https://gitcode.com/cann/asc-stl/issues/85)。
格式依据：[Ascend SIMD 类型](https://asc.gitcode.com/api/SIMD-API/basic_api/data_structures/builtin_data_types.html)、
[OCP MX v1.0](https://www.opencompute.org/documents/ocp-microscaling-formats-mx-v1-0-spec-final-pdf)。

## 关联 API

[type_traits](../../type_traits_and_utilities/asc_type_traits/asc_type_traits.md)，[numeric](../asc_numeric/asc_numeric.md)。
