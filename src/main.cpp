#include "image_cipher.hpp"
#include <iostream>

int main() {
  // se carga la imagen y se crea una matriz de pixeles con la imagen cargada
  auto img{load_image("../test.jpg")};
  auto pixel_matrix{creat_matrix_from_image(img)};

  // se carga la llave y se genera la matriz a partir de esta

  // se aplica la operacion xor entre ambas matrices
  // se guarda la imagen
  matrix_to_raw_data(pixel_matrix, img);
  write_image("../encrypted.jpg", img);

  stbi_image_free(img.data);
  std::cout.precision(19);

  auto p{generate_key_sequence(20, 0.5, 3.9)};
  for (int i{0}; i < 20; ++i) {
    std::cout << p[i] << std::endl;
  }
}
