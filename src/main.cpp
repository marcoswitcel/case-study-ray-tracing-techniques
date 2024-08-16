#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>

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

struct Render_Parameters {
  size_t width;
  size_t height;
};

bool try_load_file_scene_definition(const char *filename, Render_Parameters &parameters)
{
  std::ifstream file(filename, std::ios::in);

  if (!file.good())
  {
    return false;
  }


  std::string line;
  while (std::getline(file, line))
  {
    std::istringstream iss(line);
    std::string command;

    iss >> command;

    bool success = !iss.fail();

    if (success)
    {
      if (command == "dimension")
      {
        size_t width, height;

        iss >> width;

        if (iss.fail())
        {
          std::cout << "[Scene_Loader] falou ao parsear 'width' .\n";
          continue;
        }

        iss >> height;

        if (iss.fail())
        {
          std::cout << "[Scene_Loader] falou ao parsear 'height' .\n";
          continue;
        }

        parameters.width = width;
        parameters.height = height;
      }
    }
  }

  return true;
}

int main(int argc, const char *argv[])
{
  std::cout << "Iniciando...\n";

  if (argc != 3)
  {
    std::cout << "Parâmetro --scene mal configurado ou faltando.\n";
    return EXIT_FAILURE;
  }

  if (!strcmp(argv[1], "scene"))
  {
    std::cout << "Parâmetro --scene não configurado corretamente.\n";
    return EXIT_FAILURE;
  }

  const char *scene_filename = argv[2];

  Render_Parameters render_parameters = {};

  if (!try_load_file_scene_definition(scene_filename, render_parameters))
  {
    printf("Arquivo '%s' não pode ser carregado.\n", scene_filename);    
  }

  export_ppm_sample();

  std::cout << "Concluído...\n";
  
  return EXIT_SUCCESS;
}
