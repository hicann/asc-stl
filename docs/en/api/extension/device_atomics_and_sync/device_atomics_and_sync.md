# Device Atomics and Thread Synchronization

Device-side atomic operations, barriers, and thread synchronization.

| Header | Description |
| --- | --- |
| [asc/atomic](asc_atomic/asc_atomic.md) | Provides integer atomic operations on GM at the thread-block or device level, as well as GM references with a fixed relaxed memory order |
| [asc/barrier](asc_barrier/asc_barrier.md) | Provides barrier synchronization within a thread-block (Block) or device (Device) scope |
| [asc/latch](asc_latch/asc_latch.md) | Provides device thread synchronization based on a one-shot countdown |
| [asc/semaphore](asc_semaphore/asc_semaphore.md) | Provides device thread synchronization based on permit counting |
