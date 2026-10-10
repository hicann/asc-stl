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

#include <asc/devices>
#include <asc/stream>

#include <acl/acl.h>

namespace {

bool device_references_are_valid()
{
    return asc::device_ref(0) == asc::device_ref(0) && asc::device_ref(0) != asc::device_ref(1);
}

bool non_owning_references_are_valid(asc::stream& stream, asc::event& start)
{
    asc::stream_ref stream_view(stream.native_handle());
    asc::event_ref start_view(start.native_handle());
    return stream_view && start_view && stream_view == asc::stream_ref(stream.native_handle()) &&
        start_view == asc::event_ref(start.native_handle());
}

bool event_flow_succeeds(asc::stream& stream, asc::event& start, asc::event& stop)
{
    asc::stream_ref stream_view(stream.native_handle());
    asc::event_ref start_view(start.native_handle());
    asc::std::uint32_t priority = 0;
    bool done = false;
    if (!stream_view.priority(priority) || !stream_view.is_done(done))
        return false;
    if (!start_view.record(stream_view) || !stream_view.wait(start_view))
        return false;
    if (!stop.record(stream) || !stop.synchronize() || !stop.is_done(done) || !done)
        return false;

    float milliseconds = 0.0F;
    if (!asc::elapsed_time(start, stop, milliseconds) || milliseconds < 0.0F)
        return false;
    return stream.synchronize();
}

bool ownership_transfer_succeeds(asc::stream& stream, asc::event& start, asc::event& stop)
{
    void* stream_handle = stream.release();
    void* event_handle = start.release();
    asc::stream adopted_stream;
    asc::event adopted_event;
    if (!asc::adopt_stream(stream_handle, adopted_stream) || !asc::adopt_event(event_handle, adopted_event))
        return false;

    asc::stream moved_stream(static_cast<asc::stream&&>(adopted_stream));
    asc::event moved_event(static_cast<asc::event&&>(adopted_event));
    asc::stream assigned_stream;
    asc::event assigned_event;
    assigned_stream = static_cast<asc::stream&&>(moved_stream);
    assigned_event = static_cast<asc::event&&>(moved_event);
    return assigned_stream.close() && assigned_event.close() && stop.close();
}

}  // namespace

int run_example()
{
    if (!device_references_are_valid())
        return 1;
    asc::stream stream;
    asc::event start;
    asc::event stop;
    if (!asc::make_stream(stream) || !asc::make_event(start) || !asc::make_event(stop))
        return 2;
    if (!non_owning_references_are_valid(stream, start))
        return 3;
    if (!event_flow_succeeds(stream, start, stop))
        return 4;
    if (!ownership_transfer_succeeds(stream, start, stop))
        return 5;
    return 0;
}

int main()
{
    if (aclInit(nullptr) != 0)
        return 1;
    if (aclrtSetDevice(0) != 0) {
        (void)aclFinalize();
        return 2;
    }
    const int result = run_example();
    const bool reset = aclrtResetDevice(0) == 0;
    const bool finalized = aclFinalize() == 0;
    return result == 0 && reset && finalized ? 0 : 3;
}
