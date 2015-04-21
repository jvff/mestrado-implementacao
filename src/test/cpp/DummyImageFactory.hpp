#ifndef DUMMY_IMAGE_FACTORY_HPP
#define DUMMY_IMAGE_FACTORY_HPP

#include "ImageFactory.hpp"

#include "DestructorInterceptor.hpp"
#include "DummyImage.hpp"

typedef DestructorInterceptor<ImageFactory<DummyImage> > DummyImageFactory;

#endif
