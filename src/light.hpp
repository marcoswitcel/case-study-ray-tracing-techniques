#pragma once

#include "vec3.hpp"

enum Light_Type {
  POINT,
  DIRECTIONAL,
  AMBIENT,
};

struct Light {
  Light_Type type;
  float intensity;
  Vec3<float> position;
};