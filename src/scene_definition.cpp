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
  float viewport_width;
  float viewport_height;
  float projection_plane_d;
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

    if (iss.fail()) continue;
    
    if (command == "version")
    {
      std::string version;

      iss >> version;

      if (iss.fail())
      {
        std::cout << "[Scene_Loader] falou ao parsear 'version' .\n";
        continue;
      }

      printf("[Scene_Loader] Arquivo na versão '%s'.\n", version.c_str());
    }
    else if (command == "dimension")
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
    else if (command == "viewport")
    {
      float viewport_width, viewport_height;

      iss >> viewport_width;

      if (iss.fail())
      {
        std::cout << "[Scene_Loader] falou ao parsear 'viewport width' .\n";
        continue;
      }

      iss >> viewport_height;

      if (iss.fail())
      {
        std::cout << "[Scene_Loader] falou ao parsear 'viewport height' .\n";
        continue;
      }

      parameters.viewport_width = viewport_width;
      parameters.viewport_height = viewport_height;
    }
    else if (command == "projection_plane_d")
    {
      float d;

      iss >> d;

      if (iss.fail())
      {
        std::cout << "[Scene_Loader] falou ao parsear 'projection_plane_d' .\n";
        continue;
      }

      parameters.projection_plane_d = d;
    }
    else
    {
      printf("[Scene_Loader] instrução desconhecida '%s'.\n", command.c_str());
      continue;
    }
  }

  return true;
}
