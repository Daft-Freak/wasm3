#include <cstdio>

#include "32blit.hpp"
#include "engine/profiler.hpp"

#include "wasm3_cpp.h"
#include "assets.hpp"

blit::Profiler profiler;
blit::ProfilerProbe *profilerUpdateProbe, *profilerRenderProbe;

void screen_pen(int32_t r, int32_t g, int32_t b, int32_t a)
{
    blit::screen.pen = blit::Pen((int)r, (int)g, (int)b, (int)a);
}

void screen_pixel(int32_t x, int32_t y)
{
    blit::screen.pixel(blit::Point(x, y));
}

wasm3::environment env;
wasm3::runtime *runtime;
wasm3::module *mod;

wasm3::function *renderFn;

void init()
{
    runtime = new wasm3::runtime(env.new_runtime(1024));
    mod = new wasm3::module(env.parse_module(test_wasm, test_wasm_length));
    runtime->load(*mod);

    mod->link<screen_pen>("*", "screen_pen");
    mod->link<screen_pixel>("*", "screen_pixel");

    renderFn = new wasm3::function(runtime->find_function("_Z6renderj"));

    blit::set_screen_mode(blit::ScreenMode::hires);

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
