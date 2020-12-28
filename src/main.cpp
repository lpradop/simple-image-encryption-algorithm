#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "image_cipher.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
  // se carga la imagen y se crea una matriz de pixeles con la imagen cargada
  auto img{load_image(argv[1])};
  auto pixel_vector{create_vector_from_image(img)};
  // se carga la llave y se genera la matriz a partir de esta
  auto key_vector{create_vector_from_key(argv[2], img.width * img.height)};

  // se aplica la operacion xor entre ambas matrices
  for (unsigned int i{0}; i < pixel_vector.size(); ++i) {
    pixel_vector[i] ^= key_vector[i];
  }
  // se guarda la imagen

  vector_to_raw_data(pixel_vector, img);
  write_image(argv[3], img);
  stbi_image_free(img.data);
}
