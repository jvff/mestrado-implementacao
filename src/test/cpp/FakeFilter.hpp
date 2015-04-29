#ifndef FAKE_FILTER_HPP
#define FAKE_FILTER_HPP

#include "Filter.hpp"

#include "DestructorInterceptor.hpp"

template <typename SourceType, typename DestinationType>
class FakeFilter : public DestructorInterceptor,
        public Filter<SourceType, DestinationType> {
public:
    ImageFactory<DestinationType>* getImageFactory() {
        return this->imageFactory;
    }
};

#endif
