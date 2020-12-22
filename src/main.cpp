#define STB_IMAGE_IMPLEMENTATION
#include "dynamic_matrix.hpp"
#include "stb_image.h"
#include <iostream>

using brocolio::container::dynamic_matrix;


int rgb_to_hex(unsigned char r, unsigned char g, unsigned char b)
{
    return (r<<16) | (g<<8) | b;
}

int main() {

  int width, height, channels;
  // unsigned char
  auto img{stbi_load("../test.jpg", &width, &height, &channels, 0)};
  //0 255

  for (int i{0}; i < 9; i+=3) {
    std::cout << rgb_to_hex(img[i], img[i+1], img[i+2]) << std::endl;
  }

  // lectura en orde matricial



  dynamic_matrix<float> image{static_cast<unsigned int>(width),
                              static_cast<unsigned int>(height)};
  if (img == NULL) {
    printf("Error in loading the image\n");
    exit(1);
  }
  printf(
      "Loaded image with a width of %dpx, a height of %dpx and %d channels\n",
      width, height, channels);

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
