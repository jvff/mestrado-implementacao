#ifndef DUMMY_SIMPLE_ARRAY_IMAGE_HPP
#define DUMMY_SIMPLE_ARRAY_IMAGE_HPP

#include "SimpleArrayImage.hpp"

#include "DestructorInterceptor.hpp"
#include "DummyTypes.hpp"

class DummySimpleArrayImage : public DestructorInterceptor,
        public SimpleArrayImage<DummyType> {
public:
    DummySimpleArrayImage(int width, int height) :
	    SimpleArrayImage(width, height) {
    }
};

#endif
