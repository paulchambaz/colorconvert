#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#define MAX_STR_LEN 64

struct color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

int parse_rgb(const char *value, struct color *color);
int parse_hex(const char *value, struct color *color);
int parse_hsl(const char *value, struct color *color);
int parse_percent(const char *value, struct color *color);
int parse_ratio(const char *value, struct color *color);

void format_rgb(const struct color color, char *buffer);
void format_hex(const struct color color, char *buffer);
void format_hsl(const struct color color, char *buffer);
void format_percent(const struct color color, char *buffer);
void format_ratio(const struct color color, char *buffer);

double hue_to_rgb_comp(double p, double q, double t);

#endif
