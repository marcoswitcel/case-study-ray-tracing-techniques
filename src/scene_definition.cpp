#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "sphere.hpp"
#include "light.hpp"

struct Render_Parameters {
  size_t width;
  size_t height;
  RGB<uint8_t> background_color;
  float viewport_width;
  float viewport_height;
  float projection_plane_d;

  std::vector<Sphere> scene_objects;
  std::vector<Light> lights;
};

bool parse_vec3(std::istringstream &iss, std::string property_name, std::string command_name, Vec3<float> &position_out)
{
  std::string property;

  iss >> property;

  if (iss.fail() || property != property_name)
  {
    printf("[Scene_Loader] falhou ao parsear propriedade '%s' da %s.\n", property_name.c_str(), command_name.c_str());
    return false;
  }

  auto position = position_out;

  iss >> position.x;

  if (iss.fail())
  {
    printf("[Scene_Loader] falhou ao parsear componente 'x' da propriedade '%s' do comando %s.\n", property_name.c_str(), command_name.c_str());
    return false;
  }

  iss >> position.y;

  if (iss.fail())
  {
    printf("[Scene_Loader] falhou ao parsear componente 'y' da propriedade '%s' do comando %s.\n", property_name.c_str(), command_name.c_str());
    return false;
  }

  iss >> position.z;

  if (iss.fail())
  {
    printf("[Scene_Loader] falhou ao parsear componente 'z' da propriedade '%s' do comando %s.\n", property_name.c_str(), command_name.c_str());
    return false;
  }

  position_out = position;

  return true;
}

/**
 * @brief 
 * @note João, é necessário criar rotinas padrão para extrair atributos, isso
 * porque o código abaixo precisar ser desduplicado.
 * 
 * @param filename 
 * @param parameters 
 * @return true 
 * @return false 
 */
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
      Sphere sphere = { {0.0, 0.0, 0.0}, 1, { 0, 0, 0, }, 0 };

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

      iss >> property;

      // atributo opcional
      if (!iss.fail() && property == ".specular")
      {
        iss >> sphere.specular;

        if (iss.fail())
        {
          std::cout << "[Scene_Loader] falhou ao parsear propriedade 'specular' da esfera.\n";
          continue;
        }
      }

      parameters.scene_objects.push_back(sphere);
    }
    else if (command == "Directional_Light")
    {
      Light light = { .type = DIRECTIONAL, };

      iss >> light.intensity;

      if (iss.fail())
      {
        std::cout << "[Scene_Loader] falhou ao parsear 'intensity' da 'Directional_Light'.\n";
        continue;
      }

      if (!parse_vec3(iss, ".position", "Directional_Light", light.position)) continue;

      parameters.lights.push_back(light);
    }
    else if (command == "Point_Light")
    {
      Light light = { .type = POINT, };

      iss >> light.intensity;

      if (iss.fail())
      {
        std::cout << "[Scene_Loader] falhou ao parsear 'intensity' da 'Point_Light'.\n";
        continue;
      }

      if (!parse_vec3(iss, ".position", "Point_Light", light.position)) continue;

      parameters.lights.push_back(light);
    }
    else if (command == "Ambient_Light")
    {
      Light light = { .type = AMBIENT, };

      iss >> light.intensity;

      if (iss.fail())
      {
        std::cout << "[Scene_Loader] falhou ao parsear 'intensity' da 'Ambient_Light'.\n";
        continue;
      }

      parameters.lights.push_back(light);
    }
    else
    {
      printf("[Scene_Loader] instrução desconhecida '%s'.\n", command.c_str());
      continue;
    }
  }

  return true;
}
