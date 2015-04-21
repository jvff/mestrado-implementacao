#ifndef DUMMY_FILTER_HPP
#define DUMMY_FILTER_HPP

#include "Filter.hpp"
#include "Image.hpp"

#include "DestructorInterceptor.hpp"
#include "DummyTypes.hpp"

class DummyFilter : public DestructorInterceptor,
        public Filter<Image<DummyTypes<1> >, Image<DummyTypes<2> > > {
};

#endif
