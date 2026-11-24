# `<asc/random>`

A fixed PCG XSL-RR 128/64 oneseq engine.

| API | Purpose |
| --- | --- |
| [asc::pcg64](pcg64.md) | A fixed PCG XSL-RR 128/64 oneseq engine. |
| [asc::pcg64::default_seed](pcg64_engine_default_seed.md) | The default 64-bit seed is 0xcafef00dd15ea5e5ULL. |
| [asc::pcg64::discard](pcg64_engine_discard.md) | Advance in logarithmic time, equivalently discarding count raw results. |
| [asc::pcg64::max](pcg64_engine_max.md) | Return the exact upper bound 18446744073709551615. |
| [asc::pcg64::min](pcg64_engine_min.md) | Return the exact lower bound zero. |
| [asc::pcg64::operator()](pcg64_engine_operator_call.md) | Advance the state, then return one 64-bit result. |
| [asc::pcg64::pcg64](pcg64_engine_pcg64_engine.md) | Construct from the default seed, an explicit integer seed, or a copied state. |
| [asc::pcg64::result_type](pcg64_engine_result_type.md) | The exact unsigned 64-bit result and integer seed type. |
| [asc::pcg64::seed](pcg64_engine_seed.md) | Restart at the first result for the seed; zero and the maximum seed are valid. |
| [asc::pcg64::operator=](pcg64_copy.md) | Assign all 128 state bits and return a reference to this object. |
| [asc::operator==](operator_equal.md) | Compare the complete engine states. |
| [asc::operator!=](operator_not_equal.md) | Return the logical negation of complete state equality. |

[Previous interface migration](pcg64_engine.md)
