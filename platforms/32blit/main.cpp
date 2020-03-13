#include <cstdio>

#include "32blit.hpp"
#include "engine/profiler.hpp"

#include "wasm3_cpp.h"
#include "assets.hpp"

blit::Profiler profiler;
blit::ProfilerProbe *profilerUpdateProbe, *profilerRenderProbe;

// semi-generated Surface/screen API
int32_t get_screen() {
    return 1;
}

std::unordered_map<int32_t, blit::Surface *> surface_ptrs;

void Surface_set_clip(int32_t _this, int32_t v_x, int32_t v_y, int32_t v_w, int32_t v_h) {
  surface_ptrs.at(_this)->clip = blit::Rect(v_x, v_y, v_w, v_h);
}

int Surface_get_alpha(int32_t _this) {
  return surface_ptrs.at(_this)->alpha;
}

void Surface_set_alpha(int32_t _this, int v) {
  surface_ptrs.at(_this)->alpha = v;
}

void Surface_set_pen(int32_t _this, int v_r, int v_g, int v_b, int v_a) {
  surface_ptrs.at(_this)->pen = blit::Pen(v_r, v_g, v_b, v_a);
}

void Surface_clear(int32_t _this) {
  surface_ptrs.at(_this)->clear();
}

void Surface_pixel(int32_t _this, int32_t p_x, int32_t p_y) {
  surface_ptrs.at(_this)->pixel(blit::Point(p_x, p_y));
}

void Surface_v_span(int32_t _this, int32_t p_x, int32_t p_y, int c) {
  surface_ptrs.at(_this)->v_span(blit::Point(p_x, p_y), c);
}

void Surface_h_span(int32_t _this, int32_t p_x, int32_t p_y, int c) {
  surface_ptrs.at(_this)->h_span(blit::Point(p_x, p_y), c);
}

void Surface_rectangle(int32_t _this, int32_t r_x, int32_t r_y, int32_t r_w, int32_t r_h) {
  surface_ptrs.at(_this)->rectangle(blit::Rect(r_x, r_y, r_w, r_h));
}

void Surface_circle(int32_t _this, int32_t c_x, int32_t c_y, int32_t r) {
  surface_ptrs.at(_this)->circle(blit::Point(c_x, c_y), r);
}

void Surface_line(int32_t _this, int32_t p1_x, int32_t p1_y, int32_t p2_x, int32_t p2_y) {
  surface_ptrs.at(_this)->line(blit::Point(p1_x, p1_y), blit::Point(p2_x, p2_y));
}

void Surface_triangle(int32_t _this, int32_t p1_x, int32_t p1_y, int32_t p2_x, int32_t p2_y, int32_t p3_x, int32_t p3_y) {
  surface_ptrs.at(_this)->triangle(blit::Point(p1_x, p1_y), blit::Point(p2_x, p2_y), blit::Point(p3_x, p3_y));
}

void Surface_watermark(int32_t _this) {
  surface_ptrs.at(_this)->watermark();
}

wasm3::environment env;
wasm3::runtime *runtime;
wasm3::module *mod;

wasm3::function *renderFn;
wasm3::function *updateFn;

void init()
{
    runtime = new wasm3::runtime(env.new_runtime(1024));
    mod = new wasm3::module(env.parse_module(test_wasm, test_wasm_length));
    runtime->load(*mod);

    // surface
    surface_ptrs.emplace(1, &blit::screen);
    mod->link_optional<get_screen>("*", "get_screen");

    mod->link_optional<Surface_set_clip>("*", "Surface_set_clip");
    mod->link_optional<Surface_get_alpha>("*", "Surface_get_alpha");
    mod->link_optional<Surface_set_alpha>("*", "Surface_set_alpha");
    mod->link_optional<Surface_set_pen>("*", "Surface_set_pen");
    mod->link_optional<Surface_clear>("*", "Surface_clear");
    mod->link_optional<Surface_pixel>("*", "Surface_pixel");
    mod->link_optional<Surface_v_span>("*", "Surface_v_span");
    mod->link_optional<Surface_h_span>("*", "Surface_h_span");
    mod->link_optional<Surface_rectangle>("*", "Surface_rectangle");
    mod->link_optional<Surface_circle>("*", "Surface_circle");
    mod->link_optional<Surface_line>("*", "Surface_line");
    mod->link_optional<Surface_triangle>("*", "Surface_triangle");
    mod->link_optional<Surface_watermark>("*", "Surface_watermark");

    renderFn = new wasm3::function(runtime->find_function("_Z6renderj"));
    updateFn = new wasm3::function(runtime->find_function("_Z6updatej"));

    blit::set_screen_mode(blit::ScreenMode::hires);

    runtime->find_function("_Z4initv").call<int>();

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
