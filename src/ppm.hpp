#pragma once

#include <stddef.h>
#include <stdint.h>

enum PPM_Magic_Identifier {
  P6, // binário
  p3, // ascii/textual
};

struct PPM {
  const PPM_Magic_Identifier type;
  const size_t width;
  const size_t height;
  const uint8_t *buffer; 
};

// @todo João, função para loadar ppm

bool export_ppm_binary_file(const char *filename, const size_t width, const size_t height, const uint8_t *buffer);
