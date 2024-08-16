#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>

struct Render_Parameters {
  size_t width;
  size_t height;
};

bool try_load_scene_definition(const char *filename, Render_Parameters &parameters)
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

    if (!iss.fail())
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
      else
      {
        printf("[Scene_Loader] instrução desconhecida '%s'.\n", command.c_str());
        continue;
      }
    }
  }

  return true;
}
