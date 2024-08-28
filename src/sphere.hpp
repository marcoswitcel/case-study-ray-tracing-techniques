#pragma once

#include <stdint.h>

#include "vec3.hpp"
#include "color.hpp"

struct Sphere {
  Vec3<float> position; // center
  float radius;
  RGB<uint8_t> color;
  int specular;
};
