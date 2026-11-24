# PCG64 引擎

按 [Issue93](https://gitcode.com/cann/asc-stl/issues/93) 将 `<asc/random>` 收敛为固定的 `asc::pcg64` 类，采用 PCG XSL-RR 128/64 oneseq 算法。播种、原始输出、状态比较与对数时间 discard 的精确规则见 [API](../zh/api/extension/bit_math_numeric_random/asc_random/pcg64.md)。

移出参数模板 pcg64_engine、重复 equal_state 和 random_bijection。原 pcg64 别名的普通构造和取数写法继续使用；指定自定义模板参数或使用索引置换的代码需调整。标准随机引擎和分布使用 `<asc/std/random>`，该头不再由扩展随机入口转引。

The fixed class uses PCG XSL-RR 128/64 oneseq. The parameter template, equal_state and random_bijection are removed. Include `<asc/std/random>` explicitly for standard engines and distributions. Raw integer reproducibility does not establish a byte-layout ABI, identical distribution samples or statistical independence between tasks.
