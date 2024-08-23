#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "sphere.hpp"

struct Render_Parameters {
  size_t width;
  size_t height;
  RGB<uint8_t> background_color;
  float viewport_width;
  float viewport_height;
  float projection_plane_d;

  std::vector<Sphere> scene_objects;
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

    if (command.empty()) continue;

    if (command[0] == '#') continue;
    
    if (command == "version")
    {
      std::string version;

      iss >> version;

      if (iss.fail())
      {
        std::cout << "[Scene_Loader] falhou ao parsear 'version'.\n";
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
        std::cout << "[Scene_Loader] falhou ao parsear 'width'.\n";
        continue;
      }

      iss >> height;

      if (iss.fail())
      {
        std::cout << "[Scene_Loader] falhou ao parsear 'height'.\n";
        continue;
      }

      parameters.width = width;
      parameters.height = height;
    }
    else if (command == "background_color")
    {

      RGB<int> color;

      iss >> color.r;

      if (iss.fail())
      {
        std::cout << "[Scene_Loader] falhou ao parsear 'r' propriedade 'background_color' da esfera.\n";
        continue;
      }

      iss >> color.g;

      if (iss.fail())
      {
        std::cout << "[Scene_Loader] falhou ao parsear 'g' propriedade 'background_color' da esfera.\n";
        continue;
      }

      iss >> color.b;

      if (iss.fail())
      {
        std::cout << "[Scene_Loader] falhou ao parsear 'b' propriedade 'background_color' da esfera.\n";
        continue;
      }

      parameters.background_color.r = color.r;
      parameters.background_color.g = color.g;
      parameters.background_color.b = color.b;
    }
    else if (command == "viewport")
    {
      float viewport_width, viewport_height;

      iss >> viewport_width;

      if (iss.fail())
      {
        std::cout << "[Scene_Loader] falhou ao parsear 'viewport width'.\n";
        continue;
      }

      iss >> viewport_height;

      if (iss.fail())
      {
        std::cout << "[Scene_Loader] falhou ao parsear 'viewport height'.\n";
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
        std::cout << "[Scene_Loader] falhou ao parsear 'projection_plane_d'.\n";
        continue;
      }

      parameters.projection_plane_d = d;
    }
    else if (command == "Sphere")
    {
      Sphere sphere = { {0.0, 0.0, 0.0}, 1, { 0, 0, 0, } };

      std::string property;

      iss >> property;

      if (iss.fail() || property != ".position")
      {
        std::cout << "[Scene_Loader] falhou ao parsear propriedade 'position' da esfera.\n";
        continue;
      }

      auto position = sphere.position;

      iss >> position.x;

      if (iss.fail())
      {
        std::cout << "[Scene_Loader] falhou ao parsear 'x' propriedade 'position' da esfera.\n";
        continue;
      }

      iss >> position.y;

      if (iss.fail())
      {
        std::cout << "[Scene_Loader] falhou ao parsear 'y' propriedade 'position' da esfera.\n";
        continue;
      }

      iss >> position.z;

      if (iss.fail())
      {
        std::cout << "[Scene_Loader] falhou ao parsear 'z' propriedade 'position' da esfera.\n";
        continue;
      }

      sphere.position = position;

      iss >> property;

      if (iss.fail() || property != ".radius")
      {
        std::cout << "[Scene_Loader] falhou ao parsear propriedade 'radius' da esfera.\n";
        continue;
      }

      iss >> sphere.radius;

      if (iss.fail())
      {
        std::cout << "[Scene_Loader] falhou ao parsear propriedade 'radius' da esfera.\n";
        continue;
      }

      iss >> property;

      if (iss.fail() || property != ".color")
      {
        std::cout << "[Scene_Loader] falhou ao parsear propriedade 'color' da esfera.\n";
        continue;
      }

      RGB<int> color;

      iss >> color.r;

      if (iss.fail())
      {
        std::cout << "[Scene_Loader] falhou ao parsear 'r' propriedade 'color' da esfera.\n";
        continue;
      }

      iss >> color.g;

      if (iss.fail())
      {
        std::cout << "[Scene_Loader] falhou ao parsear 'g' propriedade 'color' da esfera.\n";
        continue;
      }

      iss >> color.b;

      if (iss.fail())
      {
        std::cout << "[Scene_Loader] falhou ao parsear 'b' propriedade 'color' da esfera.\n";
        continue;
      }

      sphere.color.r = color.r;
      sphere.color.g = color.g;
      sphere.color.b = color.b;

      parameters.scene_objects.push_back(sphere);
    }
    else if (command == "Directional_Light")
    {
      // @todo João, terminar de implementar o carregamento
    }
    else if (command == "Point_Light")
    {
      // @todo João, terminar de implementar o carregamento
    }
    else if (command == "Ambient_Light")
    {
      // @todo João, terminar de implementar o carregamento
    }
    else
    {
      printf("[Scene_Loader] instrução desconhecida '%s'.\n", command.c_str());
      continue;
    }
  }

  return true;
}
