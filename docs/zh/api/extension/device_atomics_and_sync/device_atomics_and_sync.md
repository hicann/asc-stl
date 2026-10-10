# 设备原子操作与线程同步

设备端原子操作、屏障与线程同步。

| 头文件 | 功能 |
| --- | --- |
| [asc/atomic](asc_atomic/asc_atomic.md) | 提供作用于GM的线程块级或设备级整数原子操作，以及作用于UB的线程块级宽松整数原子操作 |
| [asc/barrier](asc_barrier/asc_barrier.md) | 提供线程块（Block）或设备（Device）作用域内的屏障同步功能 |
| [asc/latch](asc_latch/asc_latch.md) | 提供基于一次性倒计数的设备线程同步功能 |
| [asc/semaphore](asc_semaphore/asc_semaphore.md) | 提供基于许可计数的设备线程同步功能 |
