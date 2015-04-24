#ifndef DUMMY_IMAGE_FACTORY_HPP
#define DUMMY_IMAGE_FACTORY_HPP

#include "ImageFactory.hpp"

#include "DestructorInterceptor.hpp"
#include "DummyTypes.hpp"
#include "MockImage.hpp"

class DummyImageFactory : public DestructorInterceptor,
        public ImageFactory<MockImage<DummyType> > {
};

#endif
