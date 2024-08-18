#pragma once

template <typename Type>
struct Image {
  size_t width;
  size_t height;

  Type *buffer;
};
