# 头文件asc/std/random

提供随机数引擎、分布和随机数生成辅助工具

## 使用方式

```cpp
#include <asc/std/random>
```

## API列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::std::generate_canonical](generate_canonical.md) | 函数模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linear_congruential_engine](linear_congruential_engine.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linear_congruential_engine::default_seed](linear_congruential_engine_default_seed.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linear_congruential_engine::discard](linear_congruential_engine_discard.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linear_congruential_engine::increment](linear_congruential_engine_increment.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linear_congruential_engine::linear_congruential_engine](linear_congruential_engine_linear_congruential_engine.md) | 构造函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linear_congruential_engine::max](linear_congruential_engine_max.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linear_congruential_engine::min](linear_congruential_engine_min.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linear_congruential_engine::modulus](linear_congruential_engine_modulus.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linear_congruential_engine::multiplier](linear_congruential_engine_multiplier.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linear_congruential_engine::`operator()`](linear_congruential_engine_operator_call.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linear_congruential_engine::result_type](linear_congruential_engine_result_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::linear_congruential_engine::seed](linear_congruential_engine_seed.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::minstd_rand](minstd_rand.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::minstd_rand0](minstd_rand0.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::philox4x32](philox4x32.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::philox4x64](philox4x64.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::philox_engine](philox_engine.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::philox_engine::default_seed](philox_engine_default_seed.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::philox_engine::discard](philox_engine_discard.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::philox_engine::max](philox_engine_max.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::philox_engine::min](philox_engine_min.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::philox_engine::multipliers](philox_engine_multipliers.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::philox_engine::`operator()`](philox_engine_operator_call.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::philox_engine::philox_engine](philox_engine_philox_engine.md) | 构造函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::philox_engine::result_type](philox_engine_result_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::philox_engine::round_consts](philox_engine_round_consts.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::philox_engine::round_count](philox_engine_round_count.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::philox_engine::seed](philox_engine_seed.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::philox_engine::set_counter](philox_engine_set_counter.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::philox_engine::word_count](philox_engine_word_count.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::philox_engine::word_size](philox_engine_word_size.md) | 变量 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_int_distribution](uniform_int_distribution.md) | 类模板 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_int_distribution::a](uniform_int_distribution_a.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_int_distribution::b](uniform_int_distribution_b.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_int_distribution::max](uniform_int_distribution_max.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_int_distribution::min](uniform_int_distribution_min.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_int_distribution::`operator()`](uniform_int_distribution_operator_call.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_int_distribution::param](uniform_int_distribution_param.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_int_distribution::param_type](uniform_int_distribution_param_type.md) | 类 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_int_distribution::reset](uniform_int_distribution_reset.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_int_distribution::result_type](uniform_int_distribution_result_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_int_distribution::uniform_int_distribution](uniform_int_distribution_uniform_int_distribution.md) | 构造函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_real_distribution](uniform_real_distribution.md) | 类特化 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::a](uniform_real_distribution_a.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::b](uniform_real_distribution_b.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::max](uniform_real_distribution_max.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::min](uniform_real_distribution_min.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::`operator()`](uniform_real_distribution_operator_call.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::param](uniform_real_distribution_param.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::param_type](uniform_real_distribution_param_type.md) | 类 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::param_type::a](uniform_real_distribution_param_type_a.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::param_type::b](uniform_real_distribution_param_type_b.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::param_type::param_type](uniform_real_distribution_param_type_param_type.md) | 构造函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::reset](uniform_real_distribution_reset.md) | 成员函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::result_type](uniform_real_distribution_result_type.md) | 类型别名 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [asc::std::uniform_real_distribution::uniform_real_distribution](uniform_real_distribution_uniform_real_distribution.md) | 构造函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [`asc::std::operator==`（philox_engine）](philox_engine_operator_equal.md) | 友元函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [`asc::std::operator==`（uniform_real_distribution）](uniform_real_distribution_operator_equal.md) | 友元函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [`asc::std::operator==`（uniform_real_distribution_param_type）](uniform_real_distribution_param_type_operator_equal.md) | 友元函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [`asc::std::operator!=`（philox_engine）](philox_engine_operator_not_equal.md) | 友元函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [`asc::std::operator!=`（uniform_real_distribution）](uniform_real_distribution_operator_not_equal.md) | 友元函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
| [`asc::std::operator!=`（uniform_real_distribution_param_type）](uniform_real_distribution_param_type_operator_not_equal.md) | 友元函数 | C++17+ | Host、AI Core SIMD编程、AI Core SIMT编程 | Ascend 950 |
