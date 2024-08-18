#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <limits>

#include "scene_definition.cpp"
#include "ppm.cpp"
#include "image.hpp"
#include "color.hpp"
#include "sphere.hpp"
#include "vec3.hpp"

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

void generate_and_export(Render_Parameters &render_parameters)
{
  const size_t width = render_parameters.width;
  const size_t height = render_parameters.height;

  uint8_t *buffer = new uint8_t[width * height * 3];

  for (size_t y = 0; y < height; y++)
  {
    for (size_t x = 0; x < width; x++)
    {
      size_t pixel_index = y * width + x;
      
      buffer[pixel_index * 3 + 0] = 255 * (x  / (float) width);
      buffer[pixel_index * 3 + 1] = 255 * (y  / (float) height);
      buffer[pixel_index * 3 + 2] = 255 * ((y + x) / (float) (width + height));
    }
  }

  export_ppm_binary_file("scene.ppm", render_parameters.width, render_parameters.height, buffer);
}

Vec3<float> canvas_to_viewport(int64_t x, int64_t y, Render_Parameters &parameters)
{
  Vec3<float> viewport = { (float) x, (float) y, parameters.projection_plane_d };
  return viewport;
}

std::pair<float, float> ray_intersect_sphere(Vec3<float> origin, Vec3<float> ray_dir, const Sphere &sphere)
{
  // @todo João, terminar de implementar

  return std::make_pair(2, 2);
}

RGB<uint8_t> trace_ray(Vec3<float> origin, Vec3<float> ray_dir, float t_min, float t_max)
{
  float closest_hit = std::numeric_limits<float>::infinity();
  const Sphere *closest_object = NULL;

  const RGB<uint8_t> background_color = { 0, 0, 0, };

  // Por hora definido aqui
  Sphere sphere01 = {
    .position = { 0, -1, 3},
    .radius = 1,
    .color = { 255, 0, 0 },
  };

  Sphere sphere02 = {
    .position = { 2, 0, 4},
    .radius = 1,
    .color = { 0, 0, 255 },
  };

  Sphere sphere03 = {
    .position = { -2, 0, 4},
    .radius = 1,
    .color = { 0, 255, 0 },
  };

  Sphere scene_objects[] = { sphere01, sphere02, sphere03, };

  for (const Sphere &object : scene_objects)
  {
    auto [ t1, t2 ] = ray_intersect_sphere(origin, ray_dir, object);

    if (t_min <= t1 && t1  <= t_max && t1 < closest_hit)
    {
      closest_hit = t1;
      closest_object = &object;
    }

    if (t_min <= t2 && t2  <= t_max && t2 < closest_hit)
    {
      closest_hit = t2;
      closest_object = &object;
    }
  }

  if (closest_object)
  {
    return closest_object->color;
  }

  return background_color;
}


void ray_trace_scene(Render_Parameters &render_parameters)
{
  const int64_t width = render_parameters.width;
  const int64_t height = render_parameters.height;

  RGB<uint8_t> *buffer = new RGB<uint8_t>[width * height];

  Vec3<float> origin = { .x = 0, .y = 0, .z = 0, };

  const auto half_width = width / 2;
  const auto half_height = height / 2;

  for (int64_t x = -1 * half_width; x <= half_width; x++)
  {
    for (int64_t y = -1 * half_height; y <= half_height; y++)
    {
      auto &pixel = buffer[(y + half_height ) * width + (x + half_width)];

      Vec3<float> ray_dir = canvas_to_viewport(x, y, render_parameters);
      pixel = trace_ray(origin, ray_dir, 1.0, std::numeric_limits<float>::infinity());
    }
  }

  export_ppm_binary_file("ray_traced_scene.ppm", render_parameters.width, render_parameters.height, (const uint8_t *)(buffer));
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

  if (!try_load_scene_definition(scene_filename, render_parameters))
  {
    printf("Arquivo '%s' não pode ser carregado.\n", scene_filename);    
  }

  generate_and_export(render_parameters);

  ray_trace_scene(render_parameters);

  export_ppm_sample();

  std::cout << "Concluído...\n";
  
  return EXIT_SUCCESS;
}
