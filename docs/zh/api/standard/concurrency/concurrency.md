# 并发支持库

原子、同步和并发操作设施。

| 头文件 | 功能 |
| --- | --- |
| [asc/std/atomic](asc_std_atomic/asc_std_atomic.md) | 提供原子读写、交换、比较交换和标准内存序控制 |
| [asc/std/barrier](asc_std_barrier/asc_std_barrier.md) | 提供可重复使用的同步屏障，使多个线程到达同一同步点后再继续执行 |
| [asc/std/latch](asc_std_latch/asc_std_latch.md) | 提供一次性倒计数同步功能；计数递减至零后，等待的线程可以继续执行 |
| [asc/std/semaphore](asc_std_semaphore/asc_std_semaphore.md) | 提供基于计数控制并发访问数量的同步功能 |
| [asc/std/mutex](asc_std_mutex/asc_std_mutex.md) | 提供互斥访问接口和锁对象管理工具 |
| [asc/std/shared_mutex](asc_std_shared_mutex/asc_std_shared_mutex.md) | 提供共享锁和独占锁，允许多个线程同时以共享方式加锁，或者由一个线程以独占方式加锁 |
