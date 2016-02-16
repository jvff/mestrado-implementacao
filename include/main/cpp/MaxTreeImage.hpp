#ifndef MAX_TREE_IMAGE_HPP
#define MAX_TREE_IMAGE_HPP

#include <functional>

#include "MinMaxTreeImage.hpp"

template <typename T>
using MaxTreeImage = MinMaxTreeImage<T, std::less<typename T::PixelType> >;

#endif
