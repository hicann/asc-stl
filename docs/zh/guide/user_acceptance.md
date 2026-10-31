# 用户场景验收与性能基线

发布验收需要同时检查结果正确、按文档可完成操作，以及目标环境中的实际耗时。
以下场景是有限的代表性验收，不表示所有API、输入、芯片或CANN版本均已覆盖。

| 用户任务 | 可执行入口 | 结果判断 |
| --- | --- | --- |
| 对32768条整数记录排序 | `scripts/run_user_acceptance.py` | 逐元素检查独立推导的有序值 |
| 连续追加65536个元素并管理存储 | 同上 | 检查全部元素、大小及校验和；另测扩容时自引用追加 |
| 通过二维视图更新256×256矩阵 | 同上 | 将每个元素与直接下标公式比较 |
| 编译、启动核函数并回拷结果 | [完整快速入门](../quick_start.md) | 核函数输出必须符合Host独立预期，资源清理成功 |
| 提交设备并行算法 | [并行算法完整工程](../../../examples/extension/parallel_algorithms/README.md) | 57个案例分别检查输入、同步、结果及清理 |
| 管理Runtime资源 | `scripts/check_api_docs.py --examples --mode runtime` | 按登记区分实际执行与仅编译，缺依赖或未运行不算执行通过 |

## Host场景和基线

在产品仓根目录执行，报告目录必须尚不存在：

```bash
python3 scripts/run_user_acceptance.py \
  --compiler g++-13 --samples 7 --report-dir /path/to/new/host-acceptance
```

脚本用同一编译器和`-O3`分别构建C++17、C++20下的ASC-STL实现和对照实现。
排序及容器对照为Host标准库；二维视图对照为直接行主序下标。每项预热一次后记录
7次耗时，并输出中位数与ASC-STL/对照比值。比值小于1仅表示该次场景耗时更少。
不设置任意的性能通过阈值；正确性失败、子进程失败、结果缺失或运行期间源码变化
都会令命令失败。

计时包括该任务的分配、初始化、操作及结果检查，属于完整Host工作负载耗时，
不是单条API延迟或Device核函数性能。报告保留全部样本、结果校验和、编译命令、
二进制及源码摘要、提交和工作目录状态、编译器与机器身份。报告里的脏工作目录
表示开发检查，正式验收应使用已提交且干净的产品版本。

执行性能测量时应停止其他编译或高负载任务，保持CPU调度与运行环境一致。
调度、温度、频率和后台负载会影响结果；不要跨机器或跨工具链直接比较比值，
也不要据此承诺其他输入规模或设备运行的性能收益。

## Device与Runtime场景

补充发布入口`ci-release-check.sh`对所选阶段采用完整通过、遇阻即停的策略。
返回码77保留为`NOT_APPLICABLE`，带环境诊断的失败保留为`BLOCKED_ENVIRONMENT`；
二者均不算已完成验收，后续阶段记为`NOT_RUN`，汇总`passed=false`且入口返回1。
这表示所选发布证据尚不完整，不必然表示产品错误，也不同于CTest对可选测试的跳过策略。
若只需独立验证Host场景，可用`--scope software --stage acceptance`和新的报告目录；
该结果只证明所选阶段，不覆盖此前未完成项。硬件预检未通过时不得继续Runtime阶段。

设备编译、cannsim和真机执行是不同证据。真机任务需要支持的Ascend设备、CANN、
驱动、正常设备健康状态以及有界的执行和同步等待。先运行快速入门的正常控制，
再串行执行并行算法和Runtime示例。首次非预期失败应停止后续任务，保留日志并重新
确认设备可用性；进程退出并不证明设备已恢复。

Runtime文档示例须在实际设备环境中按两个语言模式分别执行：

```bash
python3 scripts/check_api_docs.py --examples --mode runtime --standard 17 \
  --compiler g++ --report /path/to/runtime17.json
python3 scripts/check_api_docs.py --examples --mode runtime --standard 20 \
  --compiler g++ --report /path/to/runtime20.json
```

保留报告中的`run`、`compile_only`、`NOT_APPLICABLE`和`NOT_RUN`分类，
不能把仅编译、缺依赖或未运行计为真机语义通过。发布时应同时保留软件门禁、
文档示例、内存安全和这些场景的结果，并绑定同一产品版本；上述场景不能替代
完整Host、Device、cannsim及适用硬件回归。
