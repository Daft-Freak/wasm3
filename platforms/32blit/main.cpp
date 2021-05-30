#include <cstdio>

#include "32blit.hpp"
#include "engine/profiler.hpp"

#include "wasm3_cpp.h"
#include "assets.hpp"

blit::Profiler profiler;
blit::ProfilerProbe *profilerUpdateProbe, *profilerRenderProbe;

void link_blit_bindings(wasm3::module *mod);

// abort
void wasm_abort(void *message, void *file_name, int32_t line_number, int32_t column_number) {
    // do something
    blit::debugf("Abort!\n");
}

wasm3::environment env;
wasm3::runtime *runtime;
wasm3::module *mod = nullptr;

wasm3::function *renderFn;
wasm3::function *updateFn;

void init()
{
    runtime = new wasm3::runtime(env.new_runtime(1024));

    std::vector<uint8_t> file_data;

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

    renderFn = new wasm3::function(runtime->find_function("render"));
    updateFn = new wasm3::function(runtime->find_function("update"));

    blit::set_screen_mode(blit::ScreenMode::hires);

    runtime->find_function("init").call<int>();

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
}

void update(uint32_t time)
{
    blit::ScopedProfilerProbe scopedProbe(profilerUpdateProbe);

    updateFn->call<int>(time);
}

void render(uint32_t time)
{
    //blit::ScopedProfilerProbe scopedProbe(profilerRenderProbe);
    profilerRenderProbe->start();
    renderFn->call<int>(time);
    profilerRenderProbe->store_elapsed_us();

    profiler.set_graph_time(profilerRenderProbe->elapsed_metrics().uMaxElapsedUs);
    profiler.display_probe_overlay(1);
}
