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
  return export_portable_anymap_format(P6, filename,  width,  height, buffer);
}

bool export_portable_anymap_format(PNM_Type type, const char *filename, const size_t width, const size_t height, const uint8_t *buffer)
{
  auto openmode = std::ios_base::out;
  auto n_channels_per_pixel = 1;
  bool is_binary = type > P3;

  if (is_binary) openmode |= std::ios_base::binary;
  if (type == P3 || type == P6) n_channels_per_pixel = 3;

  const char *magic_ident = magic_identifiers[type];

  std::ofstream ofs(filename, openmode);

  if (!ofs.is_open()) return false;

  // cabeçalho
  // primeira linha número mágico
  ofs << magic_ident << std::endl; 
  // segunda linha dimensões: largura espaço altura
  ofs << width << ' ' << height << std::endl; 
  // terceira linha: valor máximo permitido para cada componente do pixel
  if (type != P1 && type != P4)
  {
    ofs << "255" << std::endl;
  }

  // dados da imagem
  // @todo João, implementar limite de caracteres por linha...
  // @todo João, ajustar para fazer em um write apenas
  // @todo João, avaliar e decidir como receber e escrever arquivos P1 e P4
  if (is_binary)
  for (size_t i = 0; i < (width * height * n_channels_per_pixel); i += 1)
  {
    ofs << buffer[i];
  }
  else
  for (size_t i = 0, n_emmited = 0; i < (width * height * n_channels_per_pixel); i += 1, n_emmited += 1)
  {
    if (n_emmited == 3)
    {
      ofs << "\n";
      n_emmited = 0;
    }
    ofs << std::to_string(buffer[i]) << " ";
  }

  ofs.close();
  return true;
}
