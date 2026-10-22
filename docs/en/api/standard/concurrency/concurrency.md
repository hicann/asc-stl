# Concurrency Support Library

Atomics, synchronization, and concurrency facilities.

| Header | Description |
| --- | --- |
| [asc/std/atomic](asc_std_atomic/asc_std_atomic.md) | Provides atomic reads and writes, exchange, compare-exchange, and standard memory order control |
| [asc/std/barrier](asc_std_barrier/asc_std_barrier.md) | Provides reusable synchronization barriers so that multiple threads continue execution after arriving at the same synchronization point |
| [asc/std/latch](asc_std_latch/asc_std_latch.md) | Provides one-shot countdown synchronization; after the count is decremented to zero, waiting threads can continue execution |
| [asc/std/semaphore](asc_std_semaphore/asc_std_semaphore.md) | Provides counting-based synchronization that controls the number of concurrent accesses |
| [asc/std/mutex](asc_std_mutex/asc_std_mutex.md) | Provides mutual-exclusion access interfaces and lock object management utilities |
| [asc/std/shared_mutex](asc_std_shared_mutex/asc_std_shared_mutex.md) | Provides shared locks and exclusive locks, allowing multiple threads to lock in shared mode at the same time, or a single thread to lock in exclusive mode |
