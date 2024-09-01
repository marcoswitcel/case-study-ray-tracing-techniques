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
  bool is_casting_shadows;

  std::vector<Sphere> scene_objects;
  std::vector<Light> lights;
};

template <typename Type>
bool try_parse_value(std::istringstream &iss, std::string property_name, std::string command_name, Type &property_slot)
{
  iss >> property_slot;

  if (iss.fail())
  {
    printf("[Scene_Loader] falhou ao parsear o valor da propriedade '%s' da %s.\n", property_name.c_str(), command_name.c_str());
    return false;
  }

  return true;
}

template <typename Type>
bool try_parse_property_value(std::istringstream &iss, std::string property_name, std::string command_name, Type &property_slot)
{
  std::string property;

  iss >> property;

  if (iss.fail() || property != property_name)
  {
    printf("[Scene_Loader] falhou ao parsear propriedade '%s' da %s.\n", property_name.c_str(), command_name.c_str());
    return false;
  }

  return try_parse_value(iss, property_name, command_name, property_slot);
}

template <typename Type>
bool try_parse_vec3(std::istringstream &iss, std::string property_name, std::string command_name, Vec3<Type> &vec3_out)
{
  std::string property;

  iss >> property;

  if (iss.fail() || property != property_name)
  {
    printf("[Scene_Loader] falhou ao parsear propriedade '%s' da %s.\n", property_name.c_str(), command_name.c_str());
    return false;
  }

  auto vec3_local = vec3_out;

  iss >> vec3_local.x;

  if (iss.fail())
  {
    printf("[Scene_Loader] falhou ao parsear componente 'x' da propriedade '%s' do comando %s.\n", property_name.c_str(), command_name.c_str());
    return false;
  }

  iss >> vec3_local.y;

  if (iss.fail())
  {
    printf("[Scene_Loader] falhou ao parsear componente 'y' da propriedade '%s' do comando %s.\n", property_name.c_str(), command_name.c_str());
    return false;
  }

  iss >> vec3_local.z;

  if (iss.fail())
  {
    printf("[Scene_Loader] falhou ao parsear componente 'z' da propriedade '%s' do comando %s.\n", property_name.c_str(), command_name.c_str());
    return false;
  }

  vec3_out = vec3_local;

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
    else if (command == "cast_shadow")
    {
      std::string value;

      iss >> value;

      if (iss.fail())
      {
        std::cout << "[Scene_Loader] falhou ao parsear valor de 'cast_shadow'.\n";
        continue;
      }

      parameters.is_casting_shadows = (value == "true");
    }
    else if (command == "dimension")
    {
      if (!try_parse_value(iss, "width", "dimension", parameters.width)) continue;
      if (!try_parse_value(iss, "height", "dimension", parameters.height)) continue;
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
      if (!try_parse_value(iss, "width", "viewport", parameters.viewport_width)) continue;
      if (!try_parse_value(iss, "height", "viewport", parameters.viewport_height)) continue;
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
      Sphere sphere = { {0.0, 0.0, 0.0}, 1, { 0, 0, 0, }, -1 };

      if (!try_parse_vec3(iss, ".position", "Sphere", sphere.position)) continue;
      
      std::string property;

      if (!try_parse_property_value(iss, ".radius", "Sphere", sphere.radius)) continue;

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
        if (!try_parse_value(iss, ".specular", "Sphere", sphere.specular)) continue;
      }

      parameters.scene_objects.push_back(sphere);
    }
    else if (command == "Directional_Light")
    {
      Light light = { .type = DIRECTIONAL, };

      if (!try_parse_value(iss, "intensity", "Directional_Light", light.intensity)) continue;

      if (!try_parse_vec3(iss, ".position", "Directional_Light", light.position)) continue;

      parameters.lights.push_back(light);
    }
    else if (command == "Point_Light")
    {
      Light light = { .type = POINT, };

      if (!try_parse_value(iss, "intensity", "Point_Light", light.intensity)) continue;

      if (!try_parse_vec3(iss, ".position", "Point_Light", light.position)) continue;

      parameters.lights.push_back(light);
    }
    else if (command == "Ambient_Light")
    {
      Light light = { .type = AMBIENT, };

      if (!try_parse_value(iss, "intensity", "Ambient_Light", light.intensity)) continue;

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
