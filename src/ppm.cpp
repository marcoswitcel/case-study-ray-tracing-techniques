#pragma once

#include <iostream>
#include <fstream>

#include "./ppm.hpp"

// @todo João, função para loadar ppm

/**
 * Sobre o formato
 * @note http://paulbourke.net/dataformats/ppm/
 * @note https://en.wikipedia.org/wiki/Netpbm#PPM_example
 */
bool export_ppm_binary_file(const char *filename, const size_t width, const size_t height, const uint8_t *buffer)
{
  return export_ppm_binary_file(P6, filename,  width,  height, buffer);
}

bool export_ppm_binary_file(PPM_Type type, const char *filename, const size_t width, const size_t height, const uint8_t *buffer)
{
  auto openmode = std::ios_base::out;
  if (type == P6) openmode |= std::ios_base::binary;

  const char *magic_ident = magic_identifiers[type];

  std::ofstream ofs(filename, openmode);

  if (!ofs.is_open()) return false;

  // cabeçalho
  // primeira linha número mágico
  ofs << magic_ident << std::endl; 
  // segunda linha dimensões: largura espaço altura
  ofs << width << ' ' << height << std::endl; 
  // @terceira linha: valor máximo permitido para cada componente do pixel
  ofs << "255" << std::endl;

  // dados da imagem
  for (size_t i = 0; i < (width * height * 3); i += 3)
  {
    uint8_t color[3] = { buffer[i + 0], buffer[i + 1], buffer[i + 2], };

    // não falta espaço ou enters?
    ofs << color[0] << color[1] << color[2];
  }

  ofs.close();
  return true;
}
