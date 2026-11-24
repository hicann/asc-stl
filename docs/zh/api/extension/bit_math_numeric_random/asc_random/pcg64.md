# asc::pcg64

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

头文件路径为：`<asc/random>`。

固定的 PCG XSL-RR 128/64 单序列引擎。

## 声明

```cpp
namespace asc {
class pcg64 {
public:
    using result_type = asc::std::uint64_t;
    static constexpr result_type default_seed = 0xcafef00dd15ea5e5ULL;
    constexpr pcg64() noexcept;
    constexpr explicit pcg64(result_type seed) noexcept;
    constexpr pcg64(const pcg64&) noexcept = default;
    constexpr pcg64& operator=(const pcg64&) noexcept = default;
    constexpr void seed(result_type seed = default_seed) noexcept;
    constexpr result_type operator()() noexcept;
    constexpr void discard(unsigned long long count) noexcept;
    static constexpr result_type min() noexcept;
    static constexpr result_type max() noexcept;
};
constexpr bool operator==(const pcg64&, const pcg64&) noexcept;
constexpr bool operator!=(const pcg64&, const pcg64&) noexcept;
} // namespace asc
```

## 约束说明

支持 C++17/C++20 的 Host、Ascend 950 SIMT 和 SIMD 核普通整数标量代码；所有操作 constexpr、noexcept。

状态为数学整数 `S`，所有更新模 `2^128`：

```text
A = 2549297995355413924 * 2^64 + 4865540595714422341
C = 6364136223846793005 * 2^64 + 1442695040888963407
T(S) = A*S + C (mod 2^128)
seed(z): S = T(C + zero_extend_128(z))
operator(): S = T(S); result = rotr64((S >> 64) xor low64(S), S >> 122)
```

旋转数为 0..63，零位旋转保持原值。固定 A 为 1 模 4、C 为奇数，状态周期为 `2^128`。默认种子、零种子和最大种子均有确定序列。播种没有对外输出；默认构造、传入 default_seed 和 seed() 得到相同状态。

复制和赋值保留完整状态；相等对象后续序列相同，单个输出相同不足以判定状态相等。`discard(0)` 不变，`discard(n)` 等价于调用 n 次 operator()，用仿射快速幂实现 `O(log(n+1))` 推进，count 覆盖 `0..ULLONG_MAX`。调用方计算偏移须保证可表示。

相同种子和原始调用位置在受支持的 Host/Device 路径上产生相同整数。对象字节布局、原始内存序列化和 ABI 没有跨后端保证；分布结果也没有跨标准库、版本或后端逐位一致约定。

符合均匀随机位生成器协议。组合分布须显式包含 `<asc/std/random>`，可使用当前支持的整数分布、`uniform_real_distribution<float>` 和 `generate_canonical<float, Bits>`。不提供 SeedSequence 或流式读写，因此不承诺完整的标准随机数引擎要求。

每个逻辑任务私有一个引擎。例如相同 seed 下任务编号 `t < 2^32`，预留每任务 1024 次原始调用，先 discard(t*1024ULL)，再最多取 1024 个结果；偏移小于 `2^42`，序列位置不重复。固定逻辑编号和每任务调用过程后，调度顺序不改变原始结果。不同位置可有相同数值，不同 seed 或不同区间不保证统计独立。分布采样可能消耗数量不固定的原始结果，预算针对引擎调用。

用于非密码用途。XSL-RR 的大量并行长序列有已知相关性，尤其是共享低位状态的序列；区间划分不构成统计独立性证明。算法来源为 [PCG 作者参考实现的 pcg64_oneseq](https://github.com/imneme/pcg-cpp/blob/428802d1a5634f96bcd0705fab379ff0113bcf13/include/pcg_random.hpp)，质量边界见 [NumPy 的并行使用分析](https://numpy.org/doc/stable/reference/random/upgrading-pcg64.html)。


## 调用示例

```cpp
#include <asc/random>

bool example()
{
    asc::pcg64 engine(42);
    return engine() == 0x287472e87ff5705aULL;
}
```

## 关联API

- [本头文件的接口列表](asc_random.md)
