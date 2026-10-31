# 并行算法：具体输入、同步结果和有界运行

[English](README_en.md) | [示例总览](../../README.md)

## 概述

本工程通过公开`<asc/algorithm>`入口运行57个独立案例。每页API的关键代码与工程对应案例相同，
输入和预期保存在[cases.json](cases.json)，不会调用被测算法生成预期。每个案例单独初始化Runtime、
分配GM输入/输出/结果槽及8192字节GM临时区，提交后检查状态、有界等待并读回结果，再记录清理状态。
提交成功本身不作为结果通过。

## 支持环境

需要Ascend 950PR/950DT、当前支持的CANN和毕昇ASC工具链，CMake 3.20或更新版本。构建显式定义`CANN_ASC_STL_USE_SIMT_LAUNCH=1`，
并使用Clang兼容的ASC翻译单元及SIMT模式；普通GCC翻译单元不提供这些parallel入口。

## 编译运行

在仓库根目录执行；头文件默认使用本仓库include，也可显式指定：

```bash
source /usr/local/Ascend/ascend-toolkit/set_env.sh
cmake -S examples/extension/parallel_algorithms -B build/parallel_algorithms17 -DASC_STL_EXAMPLE_STANDARD=17 -DCMAKE_BUILD_TYPE=Release
cmake --build build/parallel_algorithms17 -j2
python3 examples/extension/parallel_algorithms/run.py --binary build/parallel_algorithms17/asc_stl_parallel_algorithms \
  --standard 17 --report-dir build/parallel_algorithms17/results
```

将两个构建目录及语言选项改为20，独立构建和运行C++20；不要用一个模式的结果替代另一个。
run.py会先核对二进制报告的语言模式和57个案例数量。报告目录必须尚不存在，保留每次运行的结果与日志。

## 预期结果与运行约束

成功要求runner退出码为0，results.json中passed为true，且选定范围内所有案例完成校验和清理。

- Device任务时限为10秒，通过官方`aclrtSetOpExecuteTimeOut`设置并检查返回状态。
- Stream等待时限为10000毫秒，使用官方`aclrtSynchronizeStreamWithTimeout`。
- 每个案例使用独立进程，默认40秒进程期限；超时先发送SIGTERM，允许15秒清理宽限，再发送SIGKILL。
  SIGKILL后最多再等待5秒回收；若仍未退出，记录`SIGKILL_UNREAPED`与已收到的日志并停止，不能视为设备进程已结束。
  信号处理器只设置停止标志，ACL操作仍在普通Host控制流中执行。
- 每个案例记录输入约定、提交状态、同步状态、读回值、独立golden结果及释放/销毁/重置/结束状态。
  失败清理保留相应句柄记录，不把失败当成功。同步失败时停止后续设备操作，记录未清理资源并退出失败。
- 首个非预期失败、超时或中断立即停止剩余案例。设备进程退出不证明设备已恢复；后续运行前应重新确认设备健康。

定位单例可增加`--case adjacent_difference`等名称；这份结果只表示单例范围。详细日志与results.json保存在
指定目录，其中包括二进制、案例清单和runner的SHA-256。源码提交与构建命令应随验证记录另行保存。

页面示例中的`parallel_example_context`由[共享Host上下文](parallel_example.h)提供。对页面片段做Device编译时，
除产品include目录外还需把本工程目录加入include路径，并选择SIMT及上述宏；编译成功不等于本工程运行成功。

## 文件职责

- [Host入口和资源顺序](main.cpp)
- [唯一ASC编译入口](parallel_cases.asc)通过文本包含保留下列分组和分派，避免当前CANN在多个ASC翻译单元重复定义运行时注册符号。
- [案例分派表](cases.asc)
- [案例0–9](cases_0.asc)、[案例10–19](cases_1.asc)、[案例20–29](cases_2.asc)
- [案例30–39](cases_3.asc)、[案例40–49](cases_4.asc)、[案例50–56](cases_5.asc)
- [构建配置](CMakeLists.txt)、[有界runner](run.py)
