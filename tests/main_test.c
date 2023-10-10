#include <criterion/criterion.h>
#include "color.h"

Test(color_helpers, hue_to_rgb_comp) {
  cr_assert_float_eq(hue_to_rgb_comp(0.2, 0.8, 0.1), 0.56, 1e-6);
  cr_assert_float_eq(hue_to_rgb_comp(0.2, 0.8, 0.3), 0.8, 1e-6);
  cr_assert_float_eq(hue_to_rgb_comp(0.2, 0.8, 0.5), 0.8, 1e-6);
  cr_assert_float_eq(hue_to_rgb_comp(0.2, 0.8, 0.5), 0.8, 1e-6);
}

void assert_color(const char *id, struct color color, uint8_t r, uint8_t g, uint8_t b) {
  cr_assert(r == color.r && g == color.g && b == color.b,
            "%s: expected (%d, %d, %d) but got (%d, %d, %d)",
            id, r, g, b, color.r, color.g, color.b);
}

Test(color_convert, parse_rgb) {
  struct color color;
  cr_assert_eq(parse_rgb("0,0,0", &color), 0);
  assert_color("parse_rgb", color, 0, 0, 0);
  cr_assert_eq(parse_rgb("255,255,255", &color), 0);
  assert_color("parse_rgb", color, 255, 255, 255);
  cr_assert_eq(parse_rgb("0,191,255", &color), 0);
  assert_color("parse_rgb", color, 0, 191, 255);
  cr_assert_eq(parse_rgb("60,20,10", &color), 0);
  assert_color("parse_rgb", color, 60, 20, 10);
  cr_assert_eq(parse_rgb("60,180,60", &color), 0);
  assert_color("parse_rgb", color, 60, 180, 60);
}

Test(color_convert, parse_hex) {
  struct color color;
  cr_assert_eq(parse_hex("#000000", &color), 0);
  assert_color("parse_hex", color, 0, 0, 0);
  cr_assert_eq(parse_hex("#ffffff", &color), 0);
  assert_color("parse_hex", color, 255, 255, 255);
  cr_assert_eq(parse_hex("#00bfff", &color), 0);
  assert_color("parse_hex", color, 0, 191, 255);
  cr_assert_eq(parse_hex("#3c140a", &color), 0);
  assert_color("parse_hex", color, 60, 20, 10);
  cr_assert_eq(parse_hex("#3cb43c", &color), 0);
  assert_color("parse_hex", color, 60, 180, 60);
}

Test(color_convert, parse_hsl) {
  struct color color;
  cr_assert_eq(parse_hsl("0,0,0", &color), 0);
  assert_color("parse_hsl", color, 0, 0, 0);
  cr_assert_eq(parse_hsl("0,0,100", &color), 0);
  assert_color("parse_hsl", color, 255, 255, 255);
  cr_assert_eq(parse_hsl("195,100,50", &color), 0);
  assert_color("parse_hsl", color, 0, 191, 255);
  cr_assert_eq(parse_hsl("12,70,14", &color), 0);
  assert_color("parse_hsl", color, 60, 20, 10);
  cr_assert_eq(parse_hsl("120,50.1,47.25", &color), 0);
  assert_color("parse_hsl", color, 60, 180, 60);
}

Test(color_convert, parse_percent) {
  struct color color;
  cr_assert_eq(parse_percent("0.0,0.0,0.0", &color), 0);
  assert_color("parse_percent", color, 0, 0, 0);
  cr_assert_eq(parse_percent("100.0,100.0,100.0", &color), 0);
  assert_color("parse_percent", color, 255, 255, 255);
  cr_assert_eq(parse_percent("0.0,74.91,100.0", &color), 0);
  assert_color("parse_percent", color, 0, 191, 255);
  cr_assert_eq(parse_percent("23.53,7.85,3.95", &color), 0);
  assert_color("parse_percent", color, 60, 20, 10);
  cr_assert_eq(parse_percent("23.53,70.59,23.53", &color), 0);
  assert_color("parse_percent", color, 60, 180, 60);
}

Test(color_convert, parse_ratio) {
  struct color color;
  cr_assert_eq(parse_ratio("0.0,0.0,0.0", &color), 0);
  assert_color("parse_ratio", color, 0, 0, 0);
  cr_assert_eq(parse_ratio("1.0,1.0,1.0", &color), 0);
  assert_color("parse_ratio", color, 255, 255, 255);
  cr_assert_eq(parse_ratio("0.0,0.7491,1.0", &color), 0);
  assert_color("parse_ratio", color, 0, 191, 255);
  cr_assert_eq(parse_ratio("0.2353,0.0785,0.0395", &color), 0);
  assert_color("parse_ratio", color, 60, 20, 10);
  cr_assert_eq(parse_ratio("0.2353,0.7059,0.2353", &color), 0);
  assert_color("parse_ratio", color, 60, 180, 60);
}

Test(color_convert, format_rgb) {
  char rgb[MAX_STR_LEN];
  format_rgb((const struct color) { 0, 0, 0 }, rgb);
  cr_assert_str_eq(rgb, "0,0,0");
  format_rgb((const struct color) { 255, 255, 255 }, rgb);
  cr_assert_str_eq(rgb, "255,255,255");
  format_rgb((const struct color) { 0, 191, 255 }, rgb);
  cr_assert_str_eq(rgb, "0,191,255");
  format_rgb((const struct color) { 60, 20, 10 }, rgb);
  cr_assert_str_eq(rgb, "60,20,10");
  format_rgb((const struct color) { 60, 180, 60 }, rgb);
  cr_assert_str_eq(rgb, "60,180,60");
}

Test(color_convert, rgb_to_hex) {
  char hex[MAX_STR_LEN];
  format_hex((const struct color) { 0, 0, 0 }, hex);
  cr_assert_str_eq(hex,  "#000000");
  format_hex((const struct color) { 255, 255,255 }, hex);
  cr_assert_str_eq(hex,  "#ffffff");
  format_hex((const struct color) { 0, 191,255 }, hex);
  cr_assert_str_eq(hex,  "#00bfff");
  format_hex((const struct color) { 60, 20,10 }, hex);
  cr_assert_str_eq(hex,  "#3c140a");
  format_hex((const struct color) { 60, 180,60 }, hex);
  cr_assert_str_eq(hex,  "#3cb43c");
}

Test(color_convert,  rgb_to_hsl) {
  char hsl[MAX_STR_LEN];
  format_hsl((const struct color) { 0, 0, 0 }, hsl);
  cr_assert_str_eq(hsl, "0,0,0");
  format_hsl((const struct color) { 255, 255, 255 }, hsl);
  cr_assert_str_eq(hsl, "0,0,100");
  format_hsl((const struct color) { 0, 191, 255 }, hsl);
  cr_assert_str_eq(hsl, "195,100,50");
  format_hsl((const struct color) { 60, 20, 10 }, hsl);
  cr_assert_str_eq(hsl, "12,71,13");
  format_hsl((const struct color) { 60, 180, 60 }, hsl);
  cr_assert_str_eq(hsl, "120,50,47");
}

Test(color_convert, rgb_to_percent) {
  char percent[MAX_STR_LEN];
  format_percent((const struct color) { 0, 0, 0 }, percent);
  cr_assert_str_eq(percent, "0,0,0");
  format_percent((const struct color) { 255, 255, 255 }, percent);
  cr_assert_str_eq(percent, "100,100,100");
  format_percent((const struct color) { 0, 191, 255 }, percent);
  cr_assert_str_eq(percent, "0,74,100");
  format_percent((const struct color) { 60, 20, 10 }, percent);
  cr_assert_str_eq(percent, "23,7,3");
  format_percent((const struct color) { 60, 180, 60 }, percent);
  cr_assert_str_eq(percent, "23,70,23");
}

Test(color_convert, rgb_to_ratio) {
  char ratio[MAX_STR_LEN];
  format_ratio((const struct color) { 0,0,0 }, ratio);
  cr_assert_str_eq(ratio, "0.00,0.00,0.00");
  format_ratio((const struct color) { 255,255,255 }, ratio);
  cr_assert_str_eq(ratio, "1.00,1.00,1.00");
  format_ratio((const struct color) { 0,191,255 }, ratio);
  cr_assert_str_eq(ratio, "0.00,0.75,1.00");
  format_ratio((const struct color) { 60,20,10 }, ratio);
  cr_assert_str_eq(ratio, "0.24,0.08,0.04");
  format_ratio((const struct color) { 60,180,60 }, ratio);
  cr_assert_str_eq(ratio, "0.24,0.71,0.24");
}
