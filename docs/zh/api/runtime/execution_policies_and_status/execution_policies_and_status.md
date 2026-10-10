# 设备端执行策略、执行要求与提交状态

执行策略、运行要求与异步提交状态。

| 头文件 | 功能 |
| --- | --- |
| [asc/execution](asc_execution/asc_execution.md) | 统一导出设备端执行策略、执行要求和提交状态相关接口 |
| [asc/execution.policy.h](asc_execution_policy_h/asc_execution_policy_h.md) | 提供设备端执行策略，用于关联Stream、临时工作空间和执行要求 |
| [asc/execution.require.h](asc_execution_require_h/asc_execution_require_h.md) | 提供为设备端执行策略附加执行要求的组合功能 |
| [asc/execution.determinism.h](asc_execution_determinism_h/asc_execution_determinism_h.md) | 提供并行算法的结果确定性要求，用于指定相同输入是否需要产生可重复结果 |
| [asc/execution.output_ordering.h](asc_execution_output_ordering_h/asc_execution_output_ordering_h.md) | 提供并行算法的输出顺序要求 |
| [asc/execution.tie_break.h](asc_execution_tie_break_h/asc_execution_tie_break_h.md) | 提供多个结果同时满足条件时的选择规则 |
