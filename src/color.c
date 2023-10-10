#include "color.h"

/**
 * Convert a hue component to its corresponding RGB component
 *
 * # Parameters
 * - p: Intermediate RGB value
 * - q: Intermediate RGB value
 * - t: Hue value adjusted for RGB conversion
 *
 * # Return
 * Calculated RGB component for the hue
 */
double hue_to_rgb_comp(double p, double q, double t) {
  if (t < 0.0) t += 1.0;
  if (t > 1.0) t -= 1.0;
  if (t < 1.0 / 6.0) return p + (q - p) * 6.0 * t;
  if (t < 1.0 / 2.0) return q;
  if (t < 2.0 / 3.0) return p + (q - p) * (2.0 / 3.0 - t) * 6.0;
  return p;
}

/**
 * Convert RGB value to a comma-seperated string
 *
 * # Parameters
 * - r: Red component
 * - g: Green component
 * - b: Blue component
 * - buffer: Output buffer to store the generated string
 *
 * # Return
 * 0 on sucess, 1 on failure
 */
int rgb_to_str(int r, int g, int b, char *buffer) {
  if (buffer == NULL) { return 1; }

  (void)snprintf(buffer, 12, "%d,%d,%d", r, g, b);

  return 0;
}

/**
 * Parse a RGB color string into a RGB color struct
 *
 * # Parameters
 * - value: RGB color string
 * - color: Address of the color struct
 *
 * # Return
 * 0 on success, 1 on failure
 */
int parse_rgb(const char *value, struct color *color) {
  if (value == NULL || color == NULL) { return 1; }

  int r, g, b;
  if (sscanf(value, "%d , %d , %d", &r, &g, &b) != 3) { return 1; }

  if (r < 0 || r > 255) { return 1; }
  if (g < 0 || g > 255) { return 1; }
  if (b < 0 || b > 255) { return 1; }

  *color = (struct color) { (int8_t) r, (int8_t) g, (int8_t) b };

  return 0;
}

/**
 * Parse a HEX color string into a RGB color struct
 *
 * # Parameters
 * - value: HEX color string
 * - color: Address of the color struct
 *
 * # Return
 * 0 on success, 1 on failure
 */
int parse_hex(const char *value, struct color *color) {
  if (value == NULL || color == NULL) { return 1; }

  const char *value_start = value[0] == '#' ? value + 1 : value;

  unsigned int r, g, b;
  size_t len = strlen(value_start);

  if (len != 6 || len >= MAX_STR_LEN) { return 1; }

  if (sscanf(value_start, "%2x%2x%2x", &r, &g, &b) != 3) { return 1; }

  if (r > 255) { return 1; }
  if (g > 255) { return 1; }
  if (b > 255) { return 1; }

  *color = (struct color) { (int8_t) r, (int8_t) g, (int8_t) b };

  return 0;
}

/**
 * Parse a HSL color string into a RGB color struct
 *
 * # Parameters
 * - value: HSL color string
 * - color: Address of the color struct
 *
 * # Return
 * 0 on success, 1 on failure
 */
int parse_hsl(const char *value, struct color *color) {
  if (value == NULL || color == NULL) { return 1; }

  double h, s, l;
  if (sscanf(value, "%lf , %lf , %lf", &h, &s, &l) != 3) { return 1; }
  
  if (h < 0.0 || h > 360.0) { return 1; }
  if (s < 0.0 || s > 100.0) { return 1; }
  if (l < 0.0 || l > 100.0) { return 1; }

  h /= 360.0;
  s /= 100.0;
  l /= 100.0;

  double r, g, b;
  if (s == 0) {
    r = g = b = l;
  } else {
    double q = l < 0.5 ? l * (1.0 + s) : l + s - l * s;
    double p = 2.0 * l - q;
    r = hue_to_rgb_comp(p, q, h + 1.0 / 3.0);
    g = hue_to_rgb_comp(p, q, h);
    b = hue_to_rgb_comp(p, q, h - 1.0 / 3.0);
  }

  r *= 255.0;
  g *= 255.0;
  b *= 255.0;

  *color = (struct color) { (int8_t) r, (int8_t) g, (int8_t) b };

  return 0;
}

/**
 * Parse a Percentage color string into a RGB color struct
 *
 * # Parameters
 * - value: Percentage color string
 * - color: Address of the color struct
 *
 * # Return
 * 0 on success, 1 on failure
 */
int parse_percent(const char *value, struct color *color) {
  if (value == NULL || color == NULL) { return 1; }

  float pr, pg, pb;
  if (sscanf(value, "%f , %f , %f", &pr, &pg, &pb) != 3) { return 1; }

  if (pr < 0.0 || pr > 100.0) { return 1; }
  if (pg < 0.0 || pg > 100.0) { return 1; }
  if (pb < 0.0 || pb > 100.0) { return 1; }
  
  float r = 255.0 * pr / 100.0;
  float g = 255.0 * pg / 100.0;
  float b = 255.0 * pb / 100.0;

  *color = (struct color) { (int8_t) r, (int8_t) g, (int8_t) b };

  return 0;
}

/**
 * Parse a Ratio color string into a RGB color struct
 *
 * # Parameters
 * - value: Ratio color string
 * - color: Address of the color struct
 *
 * # Return
 * 0 on success, 1 on failure
 */
int parse_ratio(const char *value, struct color *color) {
  if (value == NULL || color == NULL) { return 1; }

  float rr, rg, rb;
  if (sscanf(value, "%f , %f , %f", &rr, &rg, &rb) != 3) { return 1; }

  if (rr < 0.0 || rr > 1.0) { return 1; }
  if (rg < 0.0 || rg > 1.0) { return 1; }
  if (rb < 0.0 || rb > 1.0) { return 1; }
  
  float r = 255.0 * rr;
  float g = 255.0 * rg;
  float b = 255.0 * rb;

  *color = (struct color) { (int8_t) r, (int8_t) g, (int8_t) b };

  return 0;
}

/**
 * Format a RGB color struct into a RGB color string
 *
 * # Parameter:
 * - color: RGB color struct
 * - buffer: Address to a string buffer to write RGB color string
 */
void format_rgb(const struct color color, char *buffer) {
  if (buffer == NULL) { return; }

  (void)snprintf(buffer, 12, "%d,%d,%d", color.r, color.g, color.b);
}

/**
 * Format a RGB color struct into a HEX color string
 *
 * # Parameter:
 * - color: RGB color struct
 * - buffer: Address to a string buffer to write HEX color string
 */
void format_hex(const struct color color, char *buffer) {
  if (buffer == NULL) { return; }

  (void)snprintf(buffer, 8, "#%02x%02x%02x", color.r, color.g, color.b);
}

/**
 * Format a RGB color struct into a HSL color string
 *
 * # Parameter:
 * - color: RGB color struct
 * - buffer: Address to a string buffer to write HSL color string
 */
void format_hsl(const struct color color, char *buffer) {
  if (buffer == NULL) { return; }

  double tr = (double) color.r / 255.0;
  double tg = (double) color.g / 255.0;
  double tb = (double) color.b / 255.0;

  double h = 0, s = 0, l = 0;
  double max = fmax(tr, fmax(tg, tb));
  double min = fmin(tr, fmin(tg, tb));
  double delta = (max - min);

  if (delta == 0) {
    h = 0;
  } else if (max == tr) {
    h = fmod(((tg - tb) / delta), 6);
  } else if (max == tg) {
    h = ((tb - tr) / delta) + 2.0;
  } else if (max == tb) {
    h = ((tr - tg) / delta) + 4.0;
  }

  l = (max + min) / 2.0;

  if (l == 0.0 || l == 1.0) {
    s = 0;
  } else {
    s = delta / (1 - fabs(2 * l - 1));
  }

  (void)snprintf(buffer, 12, "%d,%d,%d", (int) (h * 60), (int) (s * 100), (int) (l * 100));
}

/**
 * Format a RGB color struct into a percentage color string
 *
 * # Parameter:
 * - color: RGB color struct
 * - buffer: Address to a string buffer to write percentage color string
 */
void format_percent(const struct color color, char *buffer) {
  if (buffer == NULL) { return; }

  float pr = 100.0 * (double) color.r / 255.0;
  float pg = 100.0 * (double) color.g / 255.0;
  float pb = 100.0 * (double) color.b / 255.0;

  (void)snprintf(buffer, 12, "%d,%d,%d", (int) pr, (int) pg, (int) pb);
}

/**
 * Format a RGB color struct into a ratio color string
 *
 * # Parameter:
 * - color: RGB color struct
 * - buffer: Address to a string buffer to write ratio color string
 */
void format_ratio(const struct color color, char *buffer) {
  if (buffer == NULL) { return; }

  float rr = (double) color.r / 255.0;
  float rg = (double) color.g / 255.0;
  float rb = (double) color.b / 255.0;

  (void)snprintf(buffer, 15, "%0.2f,%0.2f,%0.2f", rr, rg, rb);
}
