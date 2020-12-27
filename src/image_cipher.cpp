#include "image_cipher.hpp"

double logistic_chaotic_map(int n, double x_0, double r) {
  static std::vector<double> terms{x_0};

  while (n >= terms.size()) {
    auto const& last_term{terms[terms.size() - 1]};
    terms.push_back(r * last_term * (1 - last_term));
  }

  return terms[n];
}

int* generate_key_sequence(int size, double x_0, double r) {
  auto sequence{new int[size]{}};
  for (int i{0}; i < size; ++i) {
    sequence[i] =
        static_cast<int>(0x1'000'000 * logistic_chaotic_map(i, x_0, r));
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

matrix creat_matrix_from_image(image const& img) {
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