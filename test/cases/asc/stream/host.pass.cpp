/*
 * Copyright 2026 湖北多样性算力应用创新研究院 (Hubei Institute for Heterogeneous Computing Applications)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <asc/stream>

namespace {
int stream_query_status = 0;
int event_query_status = 1;
unsigned int stream_priority = 3;
int synchronized_streams = 0;
int synchronized_events = 0;
int destroyed_streams = 0;
int destroyed_events = 0;
int stream_token = 0;
int event_token = 0;
}  // namespace

extern "C" int aclrtSynchronizeStream(void*)  // NOLINT(readability/casting)
{
    ++synchronized_streams;
    return 0;
}
extern "C" int aclrtStreamQuery(void*, int* status)
{
    *status = stream_query_status;
    return 0;
}
extern "C" int aclrtStreamGetPriority(void*, unsigned int* priority)
{
    *priority = stream_priority;
    return 0;
}
extern "C" int aclrtStreamWaitEvent(void*, void*)
{
    return 0;
}
extern "C" int aclrtRecordEvent(void*, void*)
{
    return 0;
}
extern "C" int aclrtSynchronizeEvent(void*)  // NOLINT(readability/casting)
{
    ++synchronized_events;
    return 0;
}
extern "C" int aclrtQueryEventStatus(void*, int* status)
{
    *status = event_query_status;
    return 0;
}
extern "C" int aclrtCreateStreamWithConfig(void** output, unsigned int, unsigned int)
{
    *output = &stream_token;
    return 0;
}
extern "C" int aclrtDestroyStream(void*)  // NOLINT(readability/casting)
{
    ++destroyed_streams;
    return 0;
}
extern "C" int aclrtCreateEvent(void** output)
{
    *output = &event_token;
    return 0;
}
extern "C" int aclrtDestroyEvent(void*)  // NOLINT(readability/casting)
{
    ++destroyed_events;
    return 0;
}
extern "C" int aclrtEventElapsedTime(float* output, void*, void*)
{
    *output = 2.5F;
    return 0;
}

int main()
{
    asc::stream stream;
    asc::event event;
    if (!asc::make_stream(stream, 3) || !asc::make_event(event))
        return 1;
    bool done = false;
    asc::std::uint32_t priority = 0;
    if (!stream.is_done(done) || !done || !stream.priority(priority) || priority != 3)
        return 2;
    if (!event.record(stream) || !stream.wait(event) || !event.is_done(done) || !done)
        return 3;
    float elapsed = 0.0F;
    if (!asc::elapsed_time(event, event, elapsed) || elapsed != 2.5F)
        return 4;
    asc::stream moved(static_cast<asc::stream&&>(stream));
    if (stream || !moved || !moved.close() || !event.close())
        return 5;
    return synchronized_streams == 1 && synchronized_events == 1 && destroyed_streams == 1 && destroyed_events == 1 ?
        0 :
        6;
}
