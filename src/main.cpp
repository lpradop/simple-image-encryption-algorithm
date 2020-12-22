#define STB_IMAGE_IMPLEMENTATION
#include "dynamic_matrix.hpp"
#include "stb_image.h"
#include <iostream>

using brocolio::container::dynamic_matrix;

struct image {
  unsigned char* data{nullptr};
  int width{0};
  int height{0};
  int channels{0};
};
int rgb_to_decimal(unsigned char r, unsigned char g, unsigned char b) {
  return (r << 16) | (g << 8) | b;
}

image load_image(char const* filename) {
  image tmp{};
  tmp.data = stbi_load(filename, &tmp.width, &tmp.height, &tmp.channels, 0);
  if (tmp.data == nullptr) {
    throw std::runtime_error{"unable to load the image"};
  }
  return tmp;
};

dynamic_matrix<> creat_matrix_from_image(image const& img) {
  int const number_of_pixels{img.width * img.height};
  auto decimal_data{new int[number_of_pixels]};

  int i{0};
  int j{0};
  while (i < number_of_pixels) {
    decimal_data[i] =
        rgb_to_decimal(img.data[j], img.data[j + 1], img.data[j + 2]);
    j += 3;
    ++i;
  }

  dynamic_matrix<> tmp{decimal_data, static_cast<unsigned int>(img.width),
                       static_cast<unsigned int>(img.height)};

  return std::move(tmp);
}

int main() {
  auto img{load_image("../test.jpg")};
  auto pixel_matrix{creat_matrix_from_image(img)};
  stbi_image_free(img.data);


  // lectura en orde matricial
  // ...
  // AES

  // cargar la imagen en una matriz
  // matrix imagen{800X800};
  // cargar la llave(imagen) en otra matriz
  // matrix llave{800X800};

  // for(i=0;i<13;++i){
  //    resultado =xor(imagen,llave);
  //    resultado * P;
  // }
  // guardamos la imagen en el disco duro
  // y ahi termina la encriptacion
}
