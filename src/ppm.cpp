#pragma once

#include <stddef.h>
#include <stdint.h>
#include <iostream>
#include <fstream>

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

/**
 * Sobre o formato
 * @note http://paulbourke.net/dataformats/ppm/
 * @note https://en.wikipedia.org/wiki/Netpbm#PPM_example
 */
bool export_ppm_binary_file(const char *filename, const size_t width, const size_t height, const uint8_t *buffer)
{
  std::ofstream ofs(filename, std::ios_base::out | std::ios_base::binary);

  if (!ofs.is_open()) return false;

  ofs << "P6" << std::endl; // magic number
  ofs << width << ' ' << height << std::endl; // dimensões - width espaço height
  ofs << "255" << std::endl; // fixo?

  for (size_t i = 0; i < (width * height * 3); i += 3)
  {
    uint8_t color[3] = { buffer[i + 0], buffer[i + 1], buffer[i + 2], };

    // não falta espaço ou enters?
    ofs << color[0] << color[1] << color[2];
  }

  ofs.close();
  return true;
}
