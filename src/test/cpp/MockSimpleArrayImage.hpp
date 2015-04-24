#ifndef MOCK_SIMPLE_ARRAY_IMAGE_HPP
#define MOCK_SIMPLE_ARRAY_IMAGE_HPP

#include "SimpleArrayImage.hpp"

#include "DestructorInterceptor.hpp"
#include "DummyTypes.hpp"

template <typename PixelType>
class MockSimpleArrayImage : public DestructorInterceptor,
        public SimpleArrayImage<PixelType> {
public:
    MockSimpleArrayImage(int width, int height) :
            SimpleArrayImage<PixelType>(width, height) {
    }
};

#endif
