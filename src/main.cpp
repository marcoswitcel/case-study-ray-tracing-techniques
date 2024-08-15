#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "ppm.cpp"

void export_ppm_sample()
{
  uint8_t buffer[12] = {
    25, 0, 0,
    0, 255, 0,
    0, 0, 255,
    255, 255, 255
  };
  export_ppm_binary_file("out.ppm", 2, 2, buffer);
}

int main(int argc, const char *argv[])
{
  std::cout << "Iniciando...\n";

  if (argc != 3)
  {
    std::cout << "Parâmetro --scene mal configurado ou faltando.\n";
    return EXIT_FAILURE;
  }

  const char *scene_filename = argv[2];

  export_ppm_sample();

  std::cout << "Concluído...\n";
  
  return EXIT_SUCCESS;
}
