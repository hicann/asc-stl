# `<asc/numeric_types>` 基础交付接口

对应 [Issue #85](https://gitcode.com/cann/asc-stl/issues/85)，实现提交
`d8860372d706eb747ad9a86e3d47f02e89381365`。本文件冻结交付标识所覆盖的基础集合。
发行包日期标识为 `20261023`，验收执行日期为 `2026-11-16`。

## 类型与表示

| 类型 | 表示 | 大小/对齐 | 元素数 |
| --- | --- | --- | --- |
| `asc::float16` | IEEE binary16 | 2/2 | 1 |
| `asc::bfloat16` | BF16 | 2/2 | 1 |
| `asc::float8_e4m3fn` | E4M3FN，最大有限值448，支持NaN | 1/1 | 1 |
| `asc::float8_e5m2` | E5M2，最大有限值57344，支持Inf/NaN | 1/1 | 1 |
| `asc::float8_e8m0` | 0..254表示2^(code-127)，255为NaN | 1/1 | 1 |
| `asc::hifloat8` | Ascend HiFloat8编码 | 1/1 | 1 |
| `asc::float4_e2m1x2` | 两个E2M1编码 | 1/1 | 2 |
| `asc::float4_e1m2x2` | 两个E1M2编码 | 1/1 | 2 |
| `asc::int4` | 四位二补码[-8,7]，高四位为0 | 1/1 | 1 |
| `asc::int4x2` | 两个四位二补码编码 | 1/1 | 2 |

类型具有标准布局和平凡默认构造、复制、移动、赋值及析构性质。`T{}`得到全0编码；
E8M0的该编码表示2^-127。普通局部变量先写后读；数值初始化通过显式转换完成。

## 格式、编码与桥接

以下接口位于`namespace asc`，`uint8_t`等整数名称指`asc::std`对应类型。

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
template<class T> using native_numeric_t = typename numeric_format_traits<T>::native_type;
template<class T> native_numeric_t<T> to_native_numeric(T value) noexcept;
template<class T> T from_native_numeric(const native_numeric_t<T>& value) noexcept;
```

traits接受上述十种无cv/ref类型，提供`storage_type`、`format`、`bits`、`storage_bits`、
`lanes`、`has_native_type`；原生映射可用时提供`native_type`。位访问完整保留编码。
`int4`编码限定0..15；三种双元素格式的元素0/1位于低/高四位，拆包返回零扩展编码。
非法编码或索引在常量求值时拒绝，运行时进入`asc::std::terminate`。

纯Host包含无需SDK，原生桥接按编译模式、芯片及对象性质开放。BiSheng15/dav-3510
Device上下文适配FP16、BF16、三种FP8、HiFloat8及两种FP4x2；SIMD另适配int4x2。
桥接保持编码；平凡原生对象按位复制，旧版int4x2公开字节包装经属性检查后适配。

## 标量转换

```cpp
enum class rounding_mode { nearest_even = 0, toward_zero = 1, toward_positive = 2, toward_negative = 3 };
enum class saturation_mode { none = 0, finite = 1 };
template<class To, rounding_mode R = rounding_mode::nearest_even,
         saturation_mode S = saturation_mode::none, class From>
To numeric_convert(From value) noexcept;
template<class To, class From, rounding_mode R = rounding_mode::nearest_even,
         saturation_mode S = saturation_mode::none>
inline constexpr bool is_numeric_conversion_supported_v = /* supported combinations */;
```

| 源 | 目标 | 舍入 | 饱和 |
| --- | --- | --- | --- |
| float | FP16/BF16/E4M3FN/E5M2 | 四种模式 | none/finite |
| FP16/BF16/E4M3FN/E5M2 | float | 四种模式 | none/finite |
| int32_t | int4 | 四种模式 | finite，钳到[-8,7] |
| int4 | int32_t | 四种模式 | none/finite，符号扩展 |

Host浮点路径要求IEEE binary32；Device软件转换面向BiSheng15/dav-3510的SIMT/SIMD
标量上下文。严格浮点配置下提供浮点转换；不支持的类型、枚举值、目标或配置查询false且不可调用。
有限值按目标精度舍入，支持渐进下溢并保持符号零。none溢出按舍入方向产生Inf或最大有限值；
E4M3FN溢出产生规范NaN。finite将溢出及源Inf钳到带符号最大有限值。
NaN规范化为FP16 0x7e00、BF16 0x7fc0、E4M3FN 0x7f、E5M2 0x7e或float 0x7fc00000。

## 交付与验收

`CANN_ASC_STL_HAS_NUMERIC_TYPES=1`表示以上集合和适用验收已交付；具体操作由能力查询约束。
验收覆盖C++17/C++20的独立包含、类型性质、编码穷举、打包、转换边界和拒绝组合，
以及适用的Device编译、模拟和950执行。原始源码身份与复用关系见
[验收记录](numeric_types_acceptance.json)。通用类型特征由type_traits维护，普通整数检查转换由numeric维护。
