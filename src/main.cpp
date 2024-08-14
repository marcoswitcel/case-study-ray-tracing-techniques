#include <stdlib.h>
#include <stdio.h>
#include <iostream>

int main(int argc, const char *argv[])
{
  std::cout << "Iniciando...\n";

  if (argc != 3)
  {
    std::cout << "Parâmetro --scene mal configurado ou faltando.\n";
    return EXIT_FAILURE;
  }

  const char *scene_filename = argv[2];

  std::cout << "Concluído...\n";
  
  return EXIT_SUCCESS;
}
