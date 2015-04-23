#ifndef DUMMY_FILTER_HPP
#define DUMMY_FILTER_HPP

#include "Filter.hpp"
#include "Image.hpp"
#include "SimpleArrayImage.hpp"

#include "DestructorInterceptor.hpp"
#include "DummyTypes.hpp"

class DummyFilter : public DestructorInterceptor,
        public Filter<Image<DummyTypes<1> >,
                SimpleArrayImage<DummyTypes<2> > > {
public:
    ImageFactory<SimpleArrayImage<DummyTypes<2> > >* getImageFactory() {
        return imageFactory;
    }
};

#endif
