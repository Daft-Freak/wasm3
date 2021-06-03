#include <cstdio>

#include "32blit.hpp"
#include "engine/profiler.hpp"

#include "wasm3.h"
#include "wrap-helper.hpp"

#ifdef PROFILER
blit::Profiler profiler;
blit::ProfilerProbe *profilerUpdateProbe, *profilerRenderProbe, *profilerGCProbe;
#endif

void link_blit_bindings(IM3Module mod);

// abort
void wasm_abort(void *message, void *file_name, int32_t line_number, int32_t column_number) {
    // do something
    blit::debugf("Abort!\n");
}

double wasm_seed() {
    return blit::random();
}

IM3Environment env = nullptr;
IM3Runtime runtime = nullptr;
IM3Module mod = nullptr;
std::vector<uint8_t> file_data;

IM3Function render_fn, update_fn = nullptr;

IM3Function collect_fn = nullptr; // AssemblyScript GC

void init()
{
    env = m3_NewEnvironment();

    runtime = m3_NewRuntime(env, 1024, nullptr);

    auto launch_path = blit::get_launch_path();
    if(launch_path)
    {
        blit::File file(launch_path);
        file_data.resize(file.get_length());

        if(file.read(0, file_data.size(), reinterpret_cast<char *>(file_data.data())) == file_data.size())
            m3_ParseModule(env, &mod, file_data.data(), file_data.size());
    }

    if(!mod)
        return;

    m3_LoadModule(runtime, mod);

    // helpers for AssemblyScript
    m3_LinkRawFunctionEx(mod, "env", "abort", "v(**ii)", &wrap_helper<decltype(wasm_abort)>::wrap_fn, reinterpret_cast<void*>(wasm_abort));
    m3_LinkRawFunctionEx(mod, "env", "seed", "F()", &wrap_helper<decltype(wasm_seed)>::wrap_fn, reinterpret_cast<void*>(wasm_seed));

    link_blit_bindings(mod);

    IM3Function init_fn = nullptr;
    m3_FindFunction(&init_fn, runtime, "init");
    m3_FindFunction(&render_fn, runtime, "render");
    m3_FindFunction(&update_fn, runtime, "update");

    m3_FindFunction(&collect_fn, runtime, "__collect");

    if(init_fn)
        m3_Call(init_fn, 0, nullptr);

    // profiler
#ifdef PROFILER
    profiler.set_display_size(blit::screen.bounds.w, blit::screen.bounds.h);
    profiler.set_rows(5);
    profiler.set_alpha(200);
    profiler.display_history(true);

    profiler.setup_graph_element(blit::Profiler::dmCur, true, true, blit::Pen(0, 255, 0));
    profiler.setup_graph_element(blit::Profiler::dmAvg, true, true, blit::Pen(0, 255, 255));
    profiler.setup_graph_element(blit::Profiler::dmMax, true, true, blit::Pen(255, 0, 0));
    profiler.setup_graph_element(blit::Profiler::dmMin, true, true, blit::Pen(255, 255, 0));

    profilerUpdateProbe = profiler.add_probe("Update", 300);
    profilerRenderProbe = profiler.add_probe("Render", 300);
    profilerGCProbe = profiler.add_probe("GC", 300);
#endif
}

void update(uint32_t time)
{
#ifdef PROFILER
    blit::ScopedProfilerProbe scopedProbe(profilerUpdateProbe);
#endif

    if(update_fn) {
        const void *args[] = {reinterpret_cast<const void *>(&time)};
        m3_Call(update_fn, 1, args);
    }
}

void render(uint32_t time)
{
#ifdef PROFILER
    profilerRenderProbe->start();
#endif

    if(render_fn) {
        const void *args[] = {reinterpret_cast<const void *>(&time)};
        m3_Call(render_fn, 1, args);
    } else {
        blit::screen.pen = {0, 0, 0};
        blit::screen.clear();

        blit::screen.pen = {0xFF, 0xFF, 0xFF};
        blit::screen.text("No render function!", blit::minimal_font, {0, 0});
    }
#ifdef PROFILER
    profilerRenderProbe->store_elapsed_us();
#endif

    // force GC
    if(collect_fn) {
#ifdef PROFILER
        profilerGCProbe->start();
#endif
        m3_Call(collect_fn, 0, nullptr);

#ifdef PROFILER
        profilerGCProbe->store_elapsed_us();
#endif
    }

#ifdef PROFILER
    profiler.set_graph_time(profilerRenderProbe->elapsed_metrics().uMaxElapsedUs);
    profiler.display_probe_overlay(1);
#endif
}
