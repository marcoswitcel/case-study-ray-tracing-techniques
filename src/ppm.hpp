#pragma once

#include <stddef.h>
#include <stdint.h>

/**
 * @brief PPM identificadores
 * 
 */
enum PNM_Type {
  P1, // portable bitmap ASCII
  P2, // portable gray map ASCII
  P3, // portable pixel map ASCII
  P4, // portable bitmap binary
  P5, // portable gray map binary
  P6, // portable pixel map binary
};

const char *magic_identifiers[] = {
  "P1",
  "P2",
  "P3",
  "P4",
  "P5",
  "P6",
};

const char *extensions_per_type[] = {
  "pbm",
  "pgm",
  "ppm",
  "pbm",
  "pgm",
  "ppm",
};

/**
 * @brief representa um arquivo PPM carregado
 * 
 */
struct PNM_File {
  PNM_Type type;
  size_t width;
  size_t height;
  uint8_t *buffer;
};

// @todo João, função para loadar ppm

bool export_ppm_binary_file(const char *filename, const size_t width, const size_t height, const uint8_t *buffer);
bool export_portable_anymap_format(PNM_Type type, const char *filename, const size_t width, const size_t height, const uint8_t *buffer);
