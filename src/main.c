#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "color.h"

/*
 * Maximum number of argument that can be passed to the program
 */
#define MAX_ARGS 1024

void parse_args(int argc, char *argv[]);
void print_help(void);
int print_rgb(const char *rgb);
int print_hex(const char *hex);
int print_hsl(const char *hsl);
int print_percent(const char *percent);
int print_ratio(const char *ratio);
void print_color(const struct color color);

/**
 * Take command line argument for various color formats, process them, and print the colors in various representation
 *
 * # Parameters
 * - argc: Number of command line arguments
 * - argv: Array of command line arguments
 *
 * # Return
 * EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int main(int argc, char *argv[]) {
  if (argc < 2) {
    (void)fprintf(stderr, "At least one argument is required\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--help") == 0) {
      print_help();
    }
  }

  parse_args(argc, argv);
}

/**
 * Parse the color arguments and print the various color formats
 *
 * # Parameters
 * - argc: Number of command line arguments
 * - argv: Array of command line arguments
 */
void parse_args(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--rgb") == 0) {
      if (++i < argc) {
        const char *rgb = argv[i];
        if (print_rgb(rgb) != 0) {
          (void)fprintf(stderr, "Error with rgb: '%s'\n", rgb);
        }
      } else {
        (void)fprintf(stderr, "--rgb requires a value.\n");
        exit(EXIT_FAILURE);
      }
    } else if (strcmp(argv[i], "--hex") == 0) {
      if (++i < argc) {
        const char *hex = argv[i];
        if (print_hex(hex) != 0) {
          (void)fprintf(stderr, "Error with hex: '%s'\n", hex);
        }
      } else {
        (void)fprintf(stderr, "--hex requires a value.\n");
        exit(EXIT_FAILURE);
      }
    } else if (strcmp(argv[i], "--hsl") == 0) {
      if (++i < argc) {
        const char *hsl = argv[i];
        if (print_hsl(hsl) != 0) {
          (void)fprintf(stderr, "Error with hsl: '%s'\n", hsl);
        }
      } else {
        (void)fprintf(stderr, "--hsl requires a value.\n");
        exit(EXIT_FAILURE);
      }
    } else if (strcmp(argv[i], "--percent") == 0) {
      if (++i < argc) {
        const char *percent = argv[i];
        if (print_percent(percent) != 0) {
          (void)fprintf(stderr, "Error with percent: '%s'\n", percent);
        }
      } else {
        (void)fprintf(stderr, "--percent requires a value.\n");
        exit(EXIT_FAILURE);
      }
    } else if (strcmp(argv[i], "--ratio") == 0) {
      if (++i < argc) {
        const char *ratio = argv[i];
        if (print_ratio(ratio) != 0) {
          (void)fprintf(stderr, "Error with ratio: '%s'\n", ratio);
        }
      } else {
        (void)fprintf(stderr, "--ratio requires a value.\n");
        exit(EXIT_FAILURE);
      }
    } else {
      (void)fprintf(stderr, "error: '%s' did not match any arguments\n", argv[i]);
      exit(EXIT_FAILURE);
    }
  }
}

/*
 * Print help message to the stdout
 */
void print_help(void) {
  printf("Usage: colorconvert [OPTIONS] [VALUE]\n");
  printf("Options\n");
  printf("--rgb      : Specify color in RGB format\n");
  printf("--hex      : Specify color in HEX format\n");
  printf("--hsl      : Specify color in HSL format\n");
  printf("--percent  : Specify color in percentage format\n");
  printf("--ratio    : Specify color in ratio format\n");
  printf("--help     : Print this help message\n");
  exit(EXIT_SUCCESS);
}

/**
 * Convert the provided RGB value into various color formats and prints them
 *
 * # Parameters
 * - rgb: RGB color value to be converted
 *
 * # Return
 * 0 on succes, 1 on failure
 */
int print_rgb(const char *rgb) {
  struct color color;
  if (parse_rgb(rgb, &color) != 0) { return 1; }
  print_color(color);
  return 0;
}

/**
 * Convert the provided HEX value into various color formats and prints them
 *
 * # Parameters
 * - hex: HEX color value to be converted
 *
 * # Return
 * 0 on succes, 1 on failure
 */
int print_hex(const char *hex) {
  struct color color;
  if (parse_hex(hex, &color) != 0) { return 1; }
  print_color(color);
  return 0;
}

/**
 * Convert the provided HSL value into various color formats and prints them
 *
 * # Parameters
 * - hsl: HSL color value to be converted
 *
 * # Return
 * 0 on succes, 1 on failure
 */
int print_hsl(const char *hsl) {
  struct color color;
  if (parse_hsl(hsl, &color) != 0) { return 1; }
  print_color(color);
  return 0;
}

/**
 * Convert the provided color percentage value into various color formats and prints them
 *
 * # Parameters
 * - percent: Color percentage value to be converted
 *
 * # Return
 * 0 on succes, 1 on failure
 */
int print_percent(const char *percent) {
  struct color color;
  if (parse_percent(percent, &color) != 0) { return 1; }
  print_color(color);
  return 0;
}

/**
 * Convert the provided color ratio value into various color formats and prints them
 *
 * # Parameters
 * - ratio: Color ratio value to be converted
 *
 * # Return
 * 0 on succes, 1 on failure
 */
int print_ratio(const char *ratio) {
  struct color color;
  if (parse_ratio(ratio, &color) != 0) { return 1; }
  print_color(color);
  return 0;
}

/**
 * Print the color in each format
 *
 * # Parameters:
 * - color: Color struct to be printed
 */
void print_color(const struct color color) {
  char rgb[MAX_STR_LEN], hex[MAX_STR_LEN], hsl[MAX_STR_LEN], percent[MAX_STR_LEN], ratio[MAX_STR_LEN];
  format_rgb(color, rgb);
  format_hex(color, hex);
  format_hsl(color, hsl);
  format_percent(color, percent);
  format_ratio(color, ratio);
  printf("rgb: %s ; hex: %s ; hsl: %s ; percent: %s ; ratio: %s\n", rgb, hex, hsl, percent, ratio);
}
