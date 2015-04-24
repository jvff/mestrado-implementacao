#ifndef MOCK_IMAGE_FACTORY_HPP
#define MOCK_IMAGE_FACTORY_HPP

#include <gmock/gmock.h>

#include "ImageFactory.hpp"

#include "DestructorInterceptor.hpp"

template <typename ImageType>
class MockImageFactory : public DestructorInterceptor,
        public ImageFactory<ImageType> {
public:
    MOCK_METHOD2_T(createImage, ImageType*(int, int));
};

#endif
