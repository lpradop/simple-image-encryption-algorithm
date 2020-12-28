#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "image_cipher.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
  // se carga la imagen y se crea una matriz de pixeles con la imagen cargada
  auto img{load_image(argv[1])};
  auto pixel_matrix{create_matrix_from_image(img)};
  //pixel_matrix.print();
  // se carga la llave y se genera la matriz a partir de esta
  auto key_matrix{create_matrix_from_key(argv[2], img.width, img.height)};
  // se aplica la operacion xor entre ambas matrices
  std::cout << "**************************************" << std::endl;
  //key_matrix.print();
  pixel_matrix ^= key_matrix;
  std::cout << "**************************************" << std::endl;
  ///pixel_matrix.print();
  // se guarda la imagen
  matrix_to_raw_data(pixel_matrix, img);
  write_image(argv[3], img);
  stbi_image_free(img.data);
}
