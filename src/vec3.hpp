#pragma once

#include <cmath>

template <typename Type>
struct Vec3 {
  Type x;
  Type y;
  Type z;
};

/**
 * @brief 
 
 * 
 * @tparam Type 
 * @param vec 
 * @return Vec3<Type> 
 */
template <typename Type>
Vec3<Type> normalize(Vec3<Type> vec)
{
  float length = std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

  if (length)
  {
    return { vec.x / length, vec.y / length, vec.z / length };
  }

  return  { 0, 0, 0, };
}

template <typename Type>
Type length(Vec3<Type> vec)
{
  return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}
