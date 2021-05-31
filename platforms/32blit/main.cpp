#include <cstdio>

#include "32blit.hpp"
#include "engine/profiler.hpp"

#include "wasm3_cpp.h"
#include "assets.hpp"

blit::Profiler profiler;
blit::ProfilerProbe *profilerUpdateProbe, *profilerRenderProbe, *profilerGCProbe;

void link_blit_bindings(wasm3::module *mod);

// abort
void wasm_abort(void *message, void *file_name, int32_t line_number, int32_t column_number) {
    // do something
    blit::debugf("Abort!\n");
}

wasm3::environment env;
wasm3::runtime *runtime;
wasm3::module *mod = nullptr;
std::vector<uint8_t> file_data;

IM3Function render_fn, update_fn = nullptr;

IM3Function collect_fn = nullptr; // AssemblyScript GC

IM3Global blit_buttons_global = nullptr;
IM3Global blit_buttons_pressed_global = nullptr;
IM3Global blit_buttons_released_global = nullptr;

void init()
{
    runtime = new wasm3::runtime(env.new_runtime(1024));

    auto launch_path = blit::get_launch_path();
    if(launch_path)
    {
        blit::File file(launch_path);
        file_data.resize(file.get_length());

        if(file.read(0, file_data.size(), reinterpret_cast<char *>(file_data.data())) == file_data.size())
            mod = new wasm3::module(env.parse_module(file_data.data(), file_data.size()));
    }

    // fallback
    if(!mod)
        mod = new wasm3::module(env.parse_module(test_wasm, test_wasm_length));

    runtime->load(*mod);

    mod->link_optional("env", "abort", wasm_abort);

    link_blit_bindings(mod);

    IM3Function init_fn = nullptr;
    m3_FindFunction(&init_fn, runtime->get(), "init");
    m3_FindFunction(&render_fn, runtime->get(), "render");
    m3_FindFunction(&update_fn, runtime->get(), "update");

    m3_FindFunction(&collect_fn, runtime->get(), "__collect");

    blit_buttons_global = m3_FindGlobal(mod->get(), "blit.buttons");
    blit_buttons_pressed_global = m3_FindGlobal(mod->get(), "blit.buttons_pressed");
    blit_buttons_released_global = m3_FindGlobal(mod->get(), "blit.buttons_released");

    blit::set_screen_mode(blit::ScreenMode::hires);


    if(init_fn)
        m3_Call(init_fn, 0, nullptr);

    // profiler
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
}

void update(uint32_t time)
{
    blit::ScopedProfilerProbe scopedProbe(profilerUpdateProbe);

    if(blit_buttons_global) {
        M3TaggedValue val{c_m3Type_i32, blit::buttons.state};
        m3_SetGlobal(blit_buttons_global, &val);
    }

    if(blit_buttons_pressed_global) {
        M3TaggedValue val{c_m3Type_i32, blit::buttons.pressed};
        m3_SetGlobal(blit_buttons_pressed_global, &val);
    }

    if(blit_buttons_released_global) {
        M3TaggedValue val{c_m3Type_i32, blit::buttons.released};
        m3_SetGlobal(blit_buttons_released_global, &val);
    }

    if(update_fn) {
        const void *args[] = {reinterpret_cast<const void *>(&time)};
        m3_Call(update_fn, 1, args);
    }
}

void render(uint32_t time)
{
    //blit::ScopedProfilerProbe scopedProbe(profilerRenderProbe);
    profilerRenderProbe->start();
    if(render_fn) {
        const void *args[] = {reinterpret_cast<const void *>(&time)};
        m3_Call(render_fn, 1, args);
    }
    profilerRenderProbe->store_elapsed_us();

    // force GC
    if(collect_fn) {
        profilerGCProbe->start();
        m3_Call(collect_fn, 0, nullptr);
        profilerGCProbe->store_elapsed_us();
    }

    profiler.set_graph_time(profilerRenderProbe->elapsed_metrics().uMaxElapsedUs);
    profiler.display_probe_overlay(1);
}
