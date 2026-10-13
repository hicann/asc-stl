# 设备执行层次、集体操作与动态任务获取

线程层次查询、集体操作与工作领取。

| 头文件 | 功能 |
| --- | --- |
| [asc/hierarchy](asc_hierarchy/asc_hierarchy.md) | 提供线程网格、线程块、线程束和线程的维度、规模与索引查询，以及AI Core SIMD编程中的子块索引与数量查询 |
| [asc/warp](asc_warp/asc_warp.md) | 提供线程束（Warp）内的投票、值匹配、数据交换（Shuffle）和归约功能 |
| [asc/collectives](asc_collectives/asc_collectives.md) | 提供AI Core SIMT编程中的线程块归约、扫描、广播及条件判断，以及AI Core SIMD编程中的UB区间归约和扫描功能 |
| [asc/work_queue](asc_work_queue/asc_work_queue.md) | 基于调用方提供的GM原子游标，为AI Core SIMD编程的子块和AI Core SIMT编程的线程束获取互不重叠的任务区间 |
