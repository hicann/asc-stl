# 内存资源、内存池与缓冲区

设备内存资源、内存池及拥有式缓冲区。

| 头文件 | 功能 |
| --- | --- |
| [asc/memory_resource](asc_memory_resource/asc_memory_resource.md) | 提供Device内存和Host锁页内存（Pinned Memory）的资源对象、非拥有引用及显式申请、释放接口 |
| [asc/memory_pool](asc_memory_pool/asc_memory_pool.md) | 仅在Event完成后复用内存块，并支持内存回收和状态统计 |
| [asc/buffer](asc_buffer/asc_buffer.md) | 提供基于指定内存资源创建并管理连续内存的缓冲区（Buffer） |
