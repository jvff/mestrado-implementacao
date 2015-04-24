#ifndef MOCK_FILTER_HPP
#define MOCK_FILTER_HPP

#include "Filter.hpp"

#include "DestructorInterceptor.hpp"

template <typename SourceType, typename DestinationType>
class MockFilter : public DestructorInterceptor,
        public Filter<SourceType, DestinationType> {

public:
    ImageFactory<DestinationType>* getImageFactory() {
        return imageFactory;
    }
};

#endif
