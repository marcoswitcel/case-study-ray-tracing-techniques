#pragma once

template <typename Pixel_Type>
struct Image {
  size_t width;
  size_t height;

  Pixel_Type *buffer;
};
