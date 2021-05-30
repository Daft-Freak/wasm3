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
static std::unordered_map<blit::Surface *, int32_t> surface_wasm_ptrs;

static blit::Surface *get_surface(int32_t ptr) {
  return surface_ptrs.at(ptr);
}

static int32_t get_wasm_pointer(blit::Surface *ptr) {
  auto it = surface_wasm_ptrs.find(ptr);
  if(it != surface_wasm_ptrs.end())
    return it->second;

  static int32_t next_surface_ptr = 1;

  surface_ptrs.emplace(next_surface_ptr, ptr);
  surface_wasm_ptrs.emplace(ptr, next_surface_ptr);
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

static int Surface_get_format(int32_t _this) {
  return static_cast<int>(get_surface(_this)->format);
}

static int Surface_get_pixel_stride(int32_t _this) {
  return get_surface(_this)->pixel_stride;
}

static int Surface_get_row_stride(int32_t _this) {
  return get_surface(_this)->row_stride;
}

static int32_t Surface_get_mask(int32_t _this) {
  return get_wasm_pointer(get_surface(_this)->mask);
}

static void Surface_set_mask(int32_t _this, int32_t v) {
  get_surface(_this)->mask = get_surface(v);
}

static int32_t Surface_get_sprites(int32_t _this) {
  return get_wasm_pointer(get_surface(_this)->sprites);
}

static void Surface_set_sprites(int32_t _this, int32_t v) {
  get_surface(_this)->sprites = get_surface(v);
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

static int Surface_get_cols(int32_t _this) {
  return get_surface(_this)->cols;
}

static int32_t Surface_load_string(void *filename) {
  blit::debugf("SURFACE_LOAD_STRING %s\n", filename);
  //abort();
  return get_wasm_pointer(blit::Surface::load(reinterpret_cast<const char *>(filename)));
}

static int Surface_save(int32_t _this, void *filename) {
  return get_surface(_this)->save(reinterpret_cast<const char *>(filename));
}

static int32_t Surface_offset_Rect(int32_t _this, int32_t r_x, int32_t r_y, int32_t r_w, int32_t r_h) {
  return get_surface(_this)->offset({r_x, r_y, r_w, r_h});
}

static int32_t Surface_offset_Point(int32_t _this, int32_t p_x, int32_t p_y) {
  return get_surface(_this)->offset({p_x, p_y});
}

static int32_t Surface_offset_int32_t_int32_t(int32_t _this, int32_t x, int32_t y) {
  return get_surface(_this)->offset(x, y);
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

static void Surface_blit(int32_t _this, int32_t src, int32_t r_x, int32_t r_y, int32_t r_w, int32_t r_h, int32_t p_x, int32_t p_y, int hflip) {
  get_surface(_this)->blit(get_surface(src), {r_x, r_y, r_w, r_h}, {p_x, p_y}, hflip);
}

static void Surface_stretch_blit(int32_t _this, int32_t src, int32_t sr_x, int32_t sr_y, int32_t sr_w, int32_t sr_h, int32_t dr_x, int32_t dr_y, int32_t dr_w, int32_t dr_h) {
  get_surface(_this)->stretch_blit(get_surface(src), {sr_x, sr_y, sr_w, sr_h}, {dr_x, dr_y, dr_w, dr_h});
}

static void Surface_stretch_blit_vspan(int32_t _this, int32_t src, int32_t uv_x, int32_t uv_y, int sc, int32_t p_x, int32_t p_y, int dc) {
  get_surface(_this)->stretch_blit_vspan(get_surface(src), {uv_x, uv_y}, sc, {p_x, p_y}, dc);
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

static void Surface_sprite_Rect_Point_int(int32_t _this, int32_t sprite_x, int32_t sprite_y, int32_t sprite_w, int32_t sprite_h, int32_t position_x, int32_t position_y, int transform) {
  get_surface(_this)->sprite({sprite_x, sprite_y, sprite_w, sprite_h}, {position_x, position_y}, transform);
}

static void Surface_sprite_Point_Point_int(int32_t _this, int32_t sprite_x, int32_t sprite_y, int32_t position_x, int32_t position_y, int transform) {
  get_surface(_this)->sprite({sprite_x, sprite_y}, {position_x, position_y}, transform);
}

static void Surface_sprite_int_Point_int(int32_t _this, int sprite, int32_t position_x, int32_t position_y, int transform) {
  get_surface(_this)->sprite(sprite, {position_x, position_y}, transform);
}

static void Surface_sprite_Rect_Point_Point_int(int32_t _this, int32_t sprite_x, int32_t sprite_y, int32_t sprite_w, int32_t sprite_h, int32_t position_x, int32_t position_y, int32_t origin_x, int32_t origin_y, int transform) {
  get_surface(_this)->sprite({sprite_x, sprite_y, sprite_w, sprite_h}, {position_x, position_y}, {origin_x, origin_y}, uint8_t(transform));
}

static void Surface_sprite_Point_Point_Point_int(int32_t _this, int32_t sprite_x, int32_t sprite_y, int32_t position_x, int32_t position_y, int32_t origin_x, int32_t origin_y, int transform) {
  get_surface(_this)->sprite({sprite_x, sprite_y}, {position_x, position_y}, {origin_x, origin_y}, uint8_t(transform));
}

static void Surface_sprite_int_Point_Point_int(int32_t _this, int sprite, int32_t position_x, int32_t position_y, int32_t origin_x, int32_t origin_y, int transform) {
  get_surface(_this)->sprite(sprite, {position_x, position_y}, {origin_x, origin_y}, uint8_t(transform));
}

static void Surface_sprite_Rect_Point_Point_Vec2_int(int32_t _this, int32_t sprite_x, int32_t sprite_y, int32_t sprite_w, int32_t sprite_h, int32_t position_x, int32_t position_y, int32_t origin_x, int32_t origin_y, float scale_x, float scale_y, int transform) {
  get_surface(_this)->sprite({sprite_x, sprite_y, sprite_w, sprite_h}, {position_x, position_y}, {origin_x, origin_y}, blit::Vec2{scale_x, scale_y}, transform);
}

static void Surface_sprite_Point_Point_Point_Vec2_int(int32_t _this, int32_t sprite_x, int32_t sprite_y, int32_t position_x, int32_t position_y, int32_t origin_x, int32_t origin_y, float scale_x, float scale_y, int transform) {
  get_surface(_this)->sprite({sprite_x, sprite_y}, {position_x, position_y}, {origin_x, origin_y}, blit::Vec2{scale_x, scale_y}, transform);
}

static void Surface_sprite_int_Point_Point_Vec2_int(int32_t _this, int sprite, int32_t position_x, int32_t position_y, int32_t origin_x, int32_t origin_y, float scale_x, float scale_y, int transform) {
  get_surface(_this)->sprite(sprite, {position_x, position_y}, {origin_x, origin_y}, blit::Vec2{scale_x, scale_y}, transform);
}

static void Surface_sprite_Rect_Point_Point_float_int(int32_t _this, int32_t sprite_x, int32_t sprite_y, int32_t sprite_w, int32_t sprite_h, int32_t position_x, int32_t position_y, int32_t origin_x, int32_t origin_y, float scale, int transform) {
  get_surface(_this)->sprite({sprite_x, sprite_y, sprite_w, sprite_h}, {position_x, position_y}, {origin_x, origin_y}, scale, transform);
}

static void Surface_sprite_Point_Point_Point_float_int(int32_t _this, int32_t sprite_x, int32_t sprite_y, int32_t position_x, int32_t position_y, int32_t origin_x, int32_t origin_y, float scale, int transform) {
  get_surface(_this)->sprite({sprite_x, sprite_y}, {position_x, position_y}, {origin_x, origin_y}, scale, transform);
}

static void Surface_sprite_int_Point_Point_float_int(int32_t _this, int sprite, int32_t position_x, int32_t position_y, int32_t origin_x, int32_t origin_y, float scale, int transform) {
  get_surface(_this)->sprite(sprite, {position_x, position_y}, {origin_x, origin_y}, scale, transform);
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
  mod->link_optional<Surface_get_format>("*", "Surface_get_format");
  mod->link_optional<Surface_get_pixel_stride>("*", "Surface_get_pixel_stride");
  mod->link_optional<Surface_get_row_stride>("*", "Surface_get_row_stride");
  mod->link_optional<Surface_get_mask>("*", "Surface_get_mask");
  mod->link_optional<Surface_set_mask>("*", "Surface_set_mask");
  mod->link_optional<Surface_get_sprites>("*", "Surface_get_sprites");
  mod->link_optional<Surface_set_sprites>("*", "Surface_set_sprites");
  mod->link_optional<Surface_get_transparent_index>("*", "Surface_get_transparent_index");
  mod->link_optional<Surface_set_transparent_index>("*", "Surface_set_transparent_index");
  mod->link_optional<Surface_get_rows>("*", "Surface_get_rows");
  mod->link_optional<Surface_get_cols>("*", "Surface_get_cols");
  mod->link_optional<Surface_load_string>("*", "Surface_load_string");
  mod->link_optional<Surface_save>("*", "Surface_save");
  mod->link_optional<Surface_offset_Rect>("*", "Surface_offset_Rect");
  mod->link_optional<Surface_offset_Point>("*", "Surface_offset_Point");
  mod->link_optional<Surface_offset_int32_t_int32_t>("*", "Surface_offset_int32_t_int32_t");
  mod->link_optional<Surface_generate_mipmaps>("*", "Surface_generate_mipmaps");
  mod->link_optional<Surface_clear>("*", "Surface_clear");
  mod->link_optional<Surface_pixel>("*", "Surface_pixel");
  mod->link_optional<Surface_v_span>("*", "Surface_v_span");
  mod->link_optional<Surface_h_span>("*", "Surface_h_span");
  mod->link_optional<Surface_rectangle>("*", "Surface_rectangle");
  mod->link_optional<Surface_circle>("*", "Surface_circle");
  mod->link_optional<Surface_line>("*", "Surface_line");
  mod->link_optional<Surface_triangle>("*", "Surface_triangle");
  mod->link_optional<Surface_blit>("*", "Surface_blit");
  mod->link_optional<Surface_stretch_blit>("*", "Surface_stretch_blit");
  mod->link_optional<Surface_stretch_blit_vspan>("*", "Surface_stretch_blit_vspan");
  mod->link_optional<Surface_watermark>("*", "Surface_watermark");
  mod->link_optional<Surface_blit_sprite>("*", "Surface_blit_sprite");
  mod->link_optional<Surface_stretch_blit_sprite>("*", "Surface_stretch_blit_sprite");
  mod->link_optional<Surface_sprite_Rect_Point_int>("*", "Surface_sprite_Rect_Point_int");
  mod->link_optional<Surface_sprite_Point_Point_int>("*", "Surface_sprite_Point_Point_int");
  mod->link_optional<Surface_sprite_int_Point_int>("*", "Surface_sprite_int_Point_int");
  mod->link_optional<Surface_sprite_Rect_Point_Point_int>("*", "Surface_sprite_Rect_Point_Point_int");
  mod->link_optional<Surface_sprite_Point_Point_Point_int>("*", "Surface_sprite_Point_Point_Point_int");
  mod->link_optional<Surface_sprite_int_Point_Point_int>("*", "Surface_sprite_int_Point_Point_int");
  mod->link_optional<Surface_sprite_Rect_Point_Point_Vec2_int>("*", "Surface_sprite_Rect_Point_Point_Vec2_int");
  mod->link_optional<Surface_sprite_Point_Point_Point_Vec2_int>("*", "Surface_sprite_Point_Point_Point_Vec2_int");
  mod->link_optional<Surface_sprite_int_Point_Point_Vec2_int>("*", "Surface_sprite_int_Point_Point_Vec2_int");
  mod->link_optional<Surface_sprite_Rect_Point_Point_float_int>("*", "Surface_sprite_Rect_Point_Point_float_int");
  mod->link_optional<Surface_sprite_Point_Point_Point_float_int>("*", "Surface_sprite_Point_Point_Point_float_int");
  mod->link_optional<Surface_sprite_int_Point_Point_float_int>("*", "Surface_sprite_int_Point_Point_float_int");
}