# `<asc/random>`

提供固定参数的 PCG XSL-RR 128/64 oneseq 引擎。

| API | 功能 |
| --- | --- |
| [asc::pcg64](pcg64.md) | 固定的 PCG XSL-RR 128/64 单序列引擎。 |
| [asc::pcg64::default_seed](pcg64_engine_default_seed.md) | 默认整数种子。 |
| [asc::pcg64::discard](pcg64_engine_discard.md) | 以对数时间推进原始序列，等价于取数 count 次并丢弃结果。 |
| [asc::pcg64::max](pcg64_engine_max.md) | 返回精确上界 18446744073709551615。 |
| [asc::pcg64::min](pcg64_engine_min.md) | 返回精确下界 0。 |
| [asc::pcg64::operator()](pcg64_engine_operator_call.md) | 先更新状态，再产生一个 64 位结果。 |
| [asc::pcg64::pcg64](pcg64_engine_pcg64_engine.md) | 默认、整数种子或完整状态复制构造。 |
| [asc::pcg64::result_type](pcg64_engine_result_type.md) | 结果与整数种子的精确 64 位无符号类型。 |
| [asc::pcg64::seed](pcg64_engine_seed.md) | 重播种并从该种子的首个结果重新开始，0 与最大种子均有效。 |
| [asc::pcg64::operator=](pcg64_copy.md) | 赋值全部 128 位状态，保留后续序列。 |
| [asc::operator==](operator_equal.md) | 比较全部状态位，不根据单个输出判断。 |
| [asc::operator!=](operator_not_equal.md) | 返回完整状态相等比较的逻辑取反。 |

[旧接口迁移](pcg64_engine.md)
