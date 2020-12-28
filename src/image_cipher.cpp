#include "image_cipher.hpp"

int* generate_key_sequence(unsigned int size, double x_0, double lambda) {
  logistic_chaotic_map map{x_0, lambda};
  auto sequence{new int[size]{}};
  for (unsigned int i{0}; i < size; ++i) {
    sequence[i] = static_cast<int>(0x1'000'000 * map(i));
  }
  return sequence;
}

int rgb_to_decimal(unsigned char r, unsigned char g, unsigned char b) {
  return (r << 16) | (g << 8) | b;
}

rgb_color decimal_to_rgb(int color) {
  return rgb_color{static_cast<unsigned char>((color & 0xff0000) >> 16),
                   static_cast<unsigned char>((color & 0x00ff00) >> 8),
                   static_cast<unsigned char>(color & 0x0000ff)};
}

image load_image(char const* filename) {
  image tmp{};
  tmp.data = stbi_load(filename, &tmp.width, &tmp.height, &tmp.channels, 0);
  if (tmp.data == nullptr) {
    throw std::runtime_error{"unable to load the image"};
  }
  return tmp;
};

void write_image(char const* filename, image const& img) {
  stbi_write_jpg(filename, img.width, img.height, img.channels, img.data, 100);
}

matrix create_matrix_from_image(image const& img) {
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

  matrix tmp{decimal_data, static_cast<unsigned int>(img.width),
             static_cast<unsigned int>(img.height)};

  return std::move(tmp);
}

void matrix_to_raw_data(matrix const& m, image const& img) {
  int k{0};
  for (int i{0}; i < m.rows(); ++i) {
    for (int j{0}; j < m.columns(); ++j) {
      auto tmp{decimal_to_rgb(m(i, j))};
      img.data[k] = tmp.r;
      img.data[k + 1] = tmp.g;
      img.data[k + 2] = tmp.b;
      k += 3;
    }
  }
}

matrix create_matrix_from_key(char const* filename, unsigned int rows,
                              unsigned int columns) {
  std::ifstream key_file{filename};
  std::string key{};
  std::getline(key_file, key);
  auto [x_0, lambda]{generate_seed_and_lambda(key)};

  matrix tmp{generate_key_sequence(rows * columns, x_0, lambda), rows, columns};

  return std::move(tmp);
}

std::pair<double, double> generate_seed_and_lambda(std::string key) {
  double lambda{0};
  std::bitset<40> even_bits{};
  std::bitset<40> odd_bits{};
  for (int i{0}; i < 10; ++i) {
    std::bitset<8> bitform_key{static_cast<unsigned long long>(key[i])};
    lambda += static_cast<double>(key[i]);
    for (int k{0}; k < 8; k += 2) {
      even_bits[i * 8 + k] = bitform_key[k];
      even_bits[i * 8 + k + 1] = bitform_key[k + 1];
    }
  }
  lambda = (lambda / 0x8'000) + 3.875;

  double seed{static_cast<double>(even_bits.to_ulong() + odd_bits.to_ulong())};
  seed /= 0x10'000'000'000; // 2^40
  double tmp{};
  seed = std::modf(seed, &tmp);
  std::cout << seed << std::endl;
  std::cout << lambda << std::endl;
  if (seed == 0) {
    seed += 0.5;
  }
  return std::make_pair(seed, lambda);
}
