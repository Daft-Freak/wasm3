#include <unordered_map>

#define NO_DEFINITIONS
#include "wasm3_cpp.h"
#include "32blit.hpp"

// partially auto-generated

#ifdef TARGET_32BLIT_HW
static blit::Surface *get_surface(int32_t ptr) {
  return reinterpret_cast<blit::Surface *>(ptr);
}

static int32_t get_wasm_pointer(blit::Surface *ptr) {
  return reinterpret_cast<int32_t>(ptr);
}
#else
static std::unordered_map<int32_t, blit::Surface *> surface_ptrs;
static int32_t next_surface_ptr = 1;

static blit::Surface *get_surface(int32_t ptr) {
  return surface_ptrs.at(ptr);
}

static int32_t get_wasm_pointer(blit::Surface *ptr) {
  surface_ptrs.emplace(next_surface_ptr, ptr);
  return next_surface_ptr++;
}
#endif

static void Surface_set_clip(int32_t _this, int32_t v_x, int32_t v_y, int32_t v_w, int32_t v_h) {
  get_surface(_this)->clip = {v_x, v_y, v_w, v_h};
}

static int Surface_get_alpha(int32_t _this) {
  return get_surface(_this)->alpha;
}

static void Surface_set_alpha(int32_t _this, int v) {
  get_surface(_this)->alpha = v;
}

static void Surface_set_pen(int32_t _this, int v_r, int v_g, int v_b, int v_a) {
  get_surface(_this)->pen = {v_r, v_g, v_b, v_a};
}

static int Surface_get_pixel_stride(int32_t _this) {
  return get_surface(_this)->pixel_stride;
}

static void Surface_set_pixel_stride(int32_t _this, int v) {
  get_surface(_this)->pixel_stride = v;
}

static int Surface_get_row_stride(int32_t _this) {
  return get_surface(_this)->row_stride;
}

static int Surface_get_transparent_index(int32_t _this) {
  return get_surface(_this)->transparent_index;
}

static void Surface_set_transparent_index(int32_t _this, int v) {
  get_surface(_this)->transparent_index = v;
}

static int Surface_get_rows(int32_t _this) {
  return get_surface(_this)->rows;
}

static void Surface_generate_mipmaps(int32_t _this, int depth) {
  get_surface(_this)->generate_mipmaps(depth);
}

static void Surface_clear(int32_t _this) {
  get_surface(_this)->clear();
}

static void Surface_pixel(int32_t _this, int32_t p_x, int32_t p_y) {
  get_surface(_this)->pixel({p_x, p_y});
}

static void Surface_v_span(int32_t _this, int32_t p_x, int32_t p_y, int c) {
  get_surface(_this)->v_span({p_x, p_y}, c);
}

static void Surface_h_span(int32_t _this, int32_t p_x, int32_t p_y, int c) {
  get_surface(_this)->h_span({p_x, p_y}, c);
}

static void Surface_rectangle(int32_t _this, int32_t r_x, int32_t r_y, int32_t r_w, int32_t r_h) {
  get_surface(_this)->rectangle({r_x, r_y, r_w, r_h});
}

static void Surface_circle(int32_t _this, int32_t c_x, int32_t c_y, int32_t r) {
  get_surface(_this)->circle({c_x, c_y}, r);
}

static void Surface_line(int32_t _this, int32_t p1_x, int32_t p1_y, int32_t p2_x, int32_t p2_y) {
  get_surface(_this)->line({p1_x, p1_y}, {p2_x, p2_y});
}

static void Surface_triangle(int32_t _this, int32_t p1_x, int32_t p1_y, int32_t p2_x, int32_t p2_y, int32_t p3_x, int32_t p3_y) {
  get_surface(_this)->triangle({p1_x, p1_y}, {p2_x, p2_y}, {p3_x, p3_y});
}

static void Surface_watermark(int32_t _this) {
  get_surface(_this)->watermark();
}

static void Surface_blit_sprite(int32_t _this, int32_t src_x, int32_t src_y, int32_t src_w, int32_t src_h, int32_t p_x, int32_t p_y, int t) {
  get_surface(_this)->blit_sprite({src_x, src_y, src_w, src_h}, {p_x, p_y}, t);
}

static void Surface_stretch_blit_sprite(int32_t _this, int32_t src_x, int32_t src_y, int32_t src_w, int32_t src_h, int32_t r_x, int32_t r_y, int32_t r_w, int32_t r_h, int t) {
  get_surface(_this)->stretch_blit_sprite({src_x, src_y, src_w, src_h}, {r_x, r_y, r_w, r_h}, t);
}

// very manual
static int32_t get_screen() {
  static int32_t screen_ptr = get_wasm_pointer(&blit::screen);
  return screen_ptr;
}

void link_blit_bindings(wasm3::module *mod) {
  mod->link_optional<get_screen>("*", "get_screen");

  // mostly auto-generated
  mod->link_optional<Surface_set_clip>("*", "Surface_set_clip");
  mod->link_optional<Surface_get_alpha>("*", "Surface_get_alpha");
  mod->link_optional<Surface_set_alpha>("*", "Surface_set_alpha");
  mod->link_optional<Surface_set_pen>("*", "Surface_set_pen");
  mod->link_optional<Surface_get_pixel_stride>("*", "Surface_get_pixel_stride");
  mod->link_optional<Surface_set_pixel_stride>("*", "Surface_set_pixel_stride");
  mod->link_optional<Surface_get_row_stride>("*", "Surface_get_row_stride");
  mod->link_optional<Surface_get_transparent_index>("*", "Surface_get_transparent_index");
  mod->link_optional<Surface_set_transparent_index>("*", "Surface_set_transparent_index");
  mod->link_optional<Surface_get_rows>("*", "Surface_get_rows");
  mod->link_optional<Surface_generate_mipmaps>("*", "Surface_generate_mipmaps");
  mod->link_optional<Surface_clear>("*", "Surface_clear");
  mod->link_optional<Surface_pixel>("*", "Surface_pixel");
  mod->link_optional<Surface_v_span>("*", "Surface_v_span");
  mod->link_optional<Surface_h_span>("*", "Surface_h_span");
  mod->link_optional<Surface_rectangle>("*", "Surface_rectangle");
  mod->link_optional<Surface_circle>("*", "Surface_circle");
  mod->link_optional<Surface_line>("*", "Surface_line");
  mod->link_optional<Surface_triangle>("*", "Surface_triangle");
  mod->link_optional<Surface_watermark>("*", "Surface_watermark");
  mod->link_optional<Surface_blit_sprite>("*", "Surface_blit_sprite");
  mod->link_optional<Surface_stretch_blit_sprite>("*", "Surface_stretch_blit_sprite");
}