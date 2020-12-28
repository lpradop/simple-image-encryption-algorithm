#pragma once
#include "dynamic_matrix.hpp"
#include "logistic_chaotic_map.hpp"
#include "stb_image.h"
#include "stb_image_write.h"
#include <vector>
#include <fstream>
#include <bitset>
#include <cmath>
using matrix = brocolio::container::dynamic_matrix<>;

struct image {
  unsigned char* data{nullptr};
  int width{0};
  int height{0};
  int channels{0};
};

struct rgb_color {
  unsigned char r{};
  unsigned char g{};
  unsigned char b{};
};

int* generate_key_sequence(int size, double x_0, double r);
int rgb_to_decimal(unsigned char r, unsigned char g, unsigned char b);
rgb_color decimal_to_rgb(int color);
image load_image(char const* filename);
void write_image(char const* filename, image const& img);
matrix create_matrix_from_image(image const& img);
void matrix_to_raw_data(matrix const& m, image const& img);
matrix create_matrix_from_key(char const* filename,unsigned int rows,
                              unsigned int columns);
std::pair<double, double> generate_seed_and_lambda(std::string key);