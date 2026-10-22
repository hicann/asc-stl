# Header asc/std/random

Provides random number engines, distributions, and random number generation helper utilities

## Usage

```cpp
#include <asc/std/random>
```

## API List

| API | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- |
| [asc::std::generate_canonical](generate_canonical.md) | Function template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linear_congruential_engine](linear_congruential_engine.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linear_congruential_engine::default_seed](linear_congruential_engine_default_seed.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linear_congruential_engine::discard](linear_congruential_engine_discard.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linear_congruential_engine::increment](linear_congruential_engine_increment.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linear_congruential_engine::linear_congruential_engine](linear_congruential_engine_linear_congruential_engine.md) | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linear_congruential_engine::max](linear_congruential_engine_max.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linear_congruential_engine::min](linear_congruential_engine_min.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linear_congruential_engine::modulus](linear_congruential_engine_modulus.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linear_congruential_engine::multiplier](linear_congruential_engine_multiplier.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linear_congruential_engine::`operator()`](linear_congruential_engine_operator_call.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linear_congruential_engine::result_type](linear_congruential_engine_result_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::linear_congruential_engine::seed](linear_congruential_engine_seed.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::minstd_rand](minstd_rand.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::minstd_rand0](minstd_rand0.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::philox4x32](philox4x32.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::philox4x64](philox4x64.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::philox_engine](philox_engine.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::philox_engine::default_seed](philox_engine_default_seed.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::philox_engine::discard](philox_engine_discard.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::philox_engine::max](philox_engine_max.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::philox_engine::min](philox_engine_min.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::philox_engine::multipliers](philox_engine_multipliers.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::philox_engine::`operator()`](philox_engine_operator_call.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::philox_engine::philox_engine](philox_engine_philox_engine.md) | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::philox_engine::result_type](philox_engine_result_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::philox_engine::round_consts](philox_engine_round_consts.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::philox_engine::round_count](philox_engine_round_count.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::philox_engine::seed](philox_engine_seed.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::philox_engine::set_counter](philox_engine_set_counter.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::philox_engine::word_count](philox_engine_word_count.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::philox_engine::word_size](philox_engine_word_size.md) | Variable | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_int_distribution](uniform_int_distribution.md) | Class template | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_int_distribution::a](uniform_int_distribution_a.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_int_distribution::b](uniform_int_distribution_b.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_int_distribution::max](uniform_int_distribution_max.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_int_distribution::min](uniform_int_distribution_min.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_int_distribution::`operator()`](uniform_int_distribution_operator_call.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_int_distribution::param](uniform_int_distribution_param.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_int_distribution::param_type](uniform_int_distribution_param_type.md) | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_int_distribution::reset](uniform_int_distribution_reset.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_int_distribution::result_type](uniform_int_distribution_result_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_int_distribution::uniform_int_distribution](uniform_int_distribution_uniform_int_distribution.md) | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_real_distribution](uniform_real_distribution.md) | Class specialization | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_real_distribution::a](uniform_real_distribution_a.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_real_distribution::b](uniform_real_distribution_b.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_real_distribution::max](uniform_real_distribution_max.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_real_distribution::min](uniform_real_distribution_min.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_real_distribution::`operator()`](uniform_real_distribution_operator_call.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_real_distribution::param](uniform_real_distribution_param.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_real_distribution::param_type](uniform_real_distribution_param_type.md) | Class | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_real_distribution::param_type::a](uniform_real_distribution_param_type_a.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_real_distribution::param_type::b](uniform_real_distribution_param_type_b.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_real_distribution::param_type::param_type](uniform_real_distribution_param_type_param_type.md) | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_real_distribution::reset](uniform_real_distribution_reset.md) | Member function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_real_distribution::result_type](uniform_real_distribution_result_type.md) | Type alias | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [asc::std::uniform_real_distribution::uniform_real_distribution](uniform_real_distribution_uniform_real_distribution.md) | Constructor | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [`asc::std::operator==` (philox_engine)](philox_engine_operator_equal.md) | Friend function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [`asc::std::operator==` (uniform_real_distribution)](uniform_real_distribution_operator_equal.md) | Friend function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [`asc::std::operator==` (uniform_real_distribution_param_type)](uniform_real_distribution_param_type_operator_equal.md) | Friend function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [`asc::std::operator!=` (philox_engine)](philox_engine_operator_not_equal.md) | Friend function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [`asc::std::operator!=` (uniform_real_distribution)](uniform_real_distribution_operator_not_equal.md) | Friend function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
| [`asc::std::operator!=` (uniform_real_distribution_param_type)](uniform_real_distribution_param_type_operator_not_equal.md) | Friend function | C++17+ | Host, AI Core SIMD programming, AI Core SIMT programming | Ascend 950 |
