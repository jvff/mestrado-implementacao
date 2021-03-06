#ifndef MIN_TREE_IMAGE_HPP
#define MIN_TREE_IMAGE_HPP

#include "MinMaxTreeImage.hpp"

template <typename T>
using MinTreeImage = MinMaxTreeImage<T, std::greater<typename T::PixelType> >;

#endif
