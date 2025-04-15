#pragma once

#include <stddef.h>
#include <stdint.h>

/**
 * @brief PPM identificadores
 * 
 */
enum PPM_Type {
  // P1, // não suportados
  // P2, // não suportados
  // P3, // ascii/textual // não suportados
  // P5, // não suportados
  P6, // imagens coloridas armazenadas em formato binário
};

const char *magic_identifiers[] = {
  // "P1", // não suportados
  // "P2", // não suportados
  // "P3", // não suportados
  // "P5", // não suportados
  "P6",
};

/**
 * @brief representa um arquivo PPM carregado
 * 
 */
struct PPM_File {
  PPM_Type type;
  size_t width;
  size_t height;
  uint8_t *buffer;
};

// @todo João, função para loadar ppm

bool export_ppm_binary_file(const char *filename, const size_t width, const size_t height, const uint8_t *buffer);
bool export_ppm_binary_file(PPM_Type type, const char *filename, const size_t width, const size_t height, const uint8_t *buffer);
