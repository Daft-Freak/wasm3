#include <unordered_map>

#include "wrap-helper.hpp"
#include "32blit.hpp"

// partially auto-generated
#ifdef TARGET_32BLIT_HW
static blit::Font *get_font(int32_t ptr) {
  return reinterpret_cast<blit::Font *>(ptr);
}

static int32_t get_wasm_pointer(blit::Font *ptr) {
  return reinterpret_cast<int32_t>(ptr);
}
#else
static std::unordered_map<int32_t, blit::Font *> font_ptrs;
static std::unordered_map<blit::Font *, int32_t> font_wasm_ptrs;

static blit::Font *get_font(int32_t ptr) {
  return font_ptrs.at(ptr);
}

static int32_t get_wasm_pointer(blit::Font *ptr) {
  auto it = font_wasm_ptrs.find(ptr);
  if(it != font_wasm_ptrs.end())
    return it->second;

  static int32_t next_font_ptr = 1;

  font_ptrs.emplace(next_font_ptr, ptr);
  font_wasm_ptrs.emplace(ptr, next_font_ptr);
  return next_font_ptr++;
}
#endif

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

static void Surface_text_string_Font_Rect_int_int(int32_t _this, void *message, int32_t font, int32_t r_x, int32_t r_y, int32_t r_w, int32_t r_h, int variable, int align) {
  get_surface(_this)->text(reinterpret_cast<const char *>(message), *get_font(font), {r_x, r_y, r_w, r_h}, variable, static_cast<blit::TextAlign>(align));
}

static void Surface_text_string_Font_Point_int_int(int32_t _this, void *message, int32_t font, int32_t p_x, int32_t p_y, int variable, int align) {
  get_surface(_this)->text(reinterpret_cast<const char *>(message), *get_font(font), {p_x, p_y}, variable, static_cast<blit::TextAlign>(align));
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

void maybe_set_global(IM3Module mod, const char *name, int32_t val) {
  auto global = m3_FindGlobal(mod, name);
  if(!global)
    return;
  
  M3TaggedValue tag_val{c_m3Type_i32, val};
  m3_SetGlobal(global, &tag_val);
}

template<typename Ret, typename ... Args>
void link_function(IM3Module module, const char *module_name, const char *function_name, const char *sig, Ret (*function)(Args...)) {
  auto res =  m3_LinkRawFunctionEx(module, module_name, function_name, sig, &wrap_helper<Ret(Args...)>::wrap_fn, reinterpret_cast<void*>(function));

  if(res != m3Err_none && res != m3Err_functionLookupFailed)
    blit::debugf("Error linking function \"%s\": %s\n", function_name, res);
}

void link_blit_bindings(IM3Module mod) {
  link_function(mod, "*", "get_screen", "i()", get_screen);

  // hmm, these are const
  maybe_set_global(mod, "blit.outline_font", get_wasm_pointer(const_cast<blit::Font *>(&blit::outline_font)));
  maybe_set_global(mod, "blit.fat_font", get_wasm_pointer(const_cast<blit::Font *>(&blit::fat_font)));
  maybe_set_global(mod, "blit.minimal_font", get_wasm_pointer(const_cast<blit::Font *>(&blit::minimal_font)));

  // mostly auto-generated
  link_function(mod, "*", "Surface_set_clip", "v(iiiii)", Surface_set_clip);
  link_function(mod, "*", "Surface_get_alpha", "i()", Surface_get_alpha);
  link_function(mod, "*", "Surface_set_alpha", "v(ii)", Surface_set_alpha);
  link_function(mod, "*", "Surface_set_pen", "v(iiiii)", Surface_set_pen);
  link_function(mod, "*", "Surface_get_format", "i()", Surface_get_format);
  link_function(mod, "*", "Surface_get_pixel_stride", "i()", Surface_get_pixel_stride);
  link_function(mod, "*", "Surface_get_row_stride", "i()", Surface_get_row_stride);
  link_function(mod, "*", "Surface_get_mask", "i()", Surface_get_mask);
  link_function(mod, "*", "Surface_set_mask", "v(ii)", Surface_set_mask);
  link_function(mod, "*", "Surface_get_sprites", "i()", Surface_get_sprites);
  link_function(mod, "*", "Surface_set_sprites", "v(ii)", Surface_set_sprites);
  link_function(mod, "*", "Surface_get_transparent_index", "i()", Surface_get_transparent_index);
  link_function(mod, "*", "Surface_set_transparent_index", "v(ii)", Surface_set_transparent_index);
  link_function(mod, "*", "Surface_get_rows", "i()", Surface_get_rows);
  link_function(mod, "*", "Surface_get_cols", "i()", Surface_get_cols);
  link_function(mod, "*", "Surface_load_string", "i(*)", Surface_load_string);
  link_function(mod, "*", "Surface_save", "i(i*)", Surface_save);
  link_function(mod, "*", "Surface_offset_Rect", "i(iiiii)", Surface_offset_Rect);
  link_function(mod, "*", "Surface_offset_Point", "i(iii)", Surface_offset_Point);
  link_function(mod, "*", "Surface_offset_int32_t_int32_t", "i(iii)", Surface_offset_int32_t_int32_t);
  link_function(mod, "*", "Surface_generate_mipmaps", "v(ii)", Surface_generate_mipmaps);
  link_function(mod, "*", "Surface_clear", "v(i)", Surface_clear);
  link_function(mod, "*", "Surface_pixel", "v(iii)", Surface_pixel);
  link_function(mod, "*", "Surface_v_span", "v(iiii)", Surface_v_span);
  link_function(mod, "*", "Surface_h_span", "v(iiii)", Surface_h_span);
  link_function(mod, "*", "Surface_rectangle", "v(iiiii)", Surface_rectangle);
  link_function(mod, "*", "Surface_circle", "v(iiii)", Surface_circle);
  link_function(mod, "*", "Surface_line", "v(iiiii)", Surface_line);
  link_function(mod, "*", "Surface_triangle", "v(iiiiiii)", Surface_triangle);
  link_function(mod, "*", "Surface_text_string_Font_Rect_int_int", "v(i*iiiiiii)", Surface_text_string_Font_Rect_int_int);
  link_function(mod, "*", "Surface_text_string_Font_Point_int_int", "v(i*iiiii)", Surface_text_string_Font_Point_int_int);
  link_function(mod, "*", "Surface_blit", "v(iiiiiiiii)", Surface_blit);
  link_function(mod, "*", "Surface_stretch_blit", "v(iiiiiiiiii)", Surface_stretch_blit);
  link_function(mod, "*", "Surface_stretch_blit_vspan", "v(iiiiiiii)", Surface_stretch_blit_vspan);
  link_function(mod, "*", "Surface_watermark", "v(i)", Surface_watermark);
  link_function(mod, "*", "Surface_blit_sprite", "v(iiiiiiii)", Surface_blit_sprite);
  link_function(mod, "*", "Surface_stretch_blit_sprite", "v(iiiiiiiiii)", Surface_stretch_blit_sprite);
  link_function(mod, "*", "Surface_sprite_Rect_Point_int", "v(iiiiiiii)", Surface_sprite_Rect_Point_int);
  link_function(mod, "*", "Surface_sprite_Point_Point_int", "v(iiiiii)", Surface_sprite_Point_Point_int);
  link_function(mod, "*", "Surface_sprite_int_Point_int", "v(iiiii)", Surface_sprite_int_Point_int);
  link_function(mod, "*", "Surface_sprite_Rect_Point_Point_int", "v(iiiiiiiiii)", Surface_sprite_Rect_Point_Point_int);
  link_function(mod, "*", "Surface_sprite_Point_Point_Point_int", "v(iiiiiiii)", Surface_sprite_Point_Point_Point_int);
  link_function(mod, "*", "Surface_sprite_int_Point_Point_int", "v(iiiiiii)", Surface_sprite_int_Point_Point_int);
  link_function(mod, "*", "Surface_sprite_Rect_Point_Point_Vec2_int", "v(iiiiiiiiiffi)", Surface_sprite_Rect_Point_Point_Vec2_int);
  link_function(mod, "*", "Surface_sprite_Point_Point_Point_Vec2_int", "v(iiiiiiiffi)", Surface_sprite_Point_Point_Point_Vec2_int);
  link_function(mod, "*", "Surface_sprite_int_Point_Point_Vec2_int", "v(iiiiiiffi)", Surface_sprite_int_Point_Point_Vec2_int);
  link_function(mod, "*", "Surface_sprite_Rect_Point_Point_float_int", "v(iiiiiiiiifi)", Surface_sprite_Rect_Point_Point_float_int);
  link_function(mod, "*", "Surface_sprite_Point_Point_Point_float_int", "v(iiiiiiifi)", Surface_sprite_Point_Point_Point_float_int);
  link_function(mod, "*", "Surface_sprite_int_Point_Point_float_int", "v(iiiiiifi)", Surface_sprite_int_Point_Point_float_int);
}