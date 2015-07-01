#ifndef BINARIZATION_FILTER_TEST_HPP
#define BINARIZATION_FILTER_TEST_HPP

#include <gtest/gtest.h>

#include "fakeit.hpp"

#include "DummyTypes.hpp"
#include "FakeImage.hpp"

using fakeit::Mock;
using fakeit::When;

class BinarizationFilterTest : public testing::Test {
private:
    Mock<FakeImage<DummyType> > sourceImageMock;

public:
    ~BinarizationFilterTest() noexcept {
    }

protected:
    FakeImage<DummyType>& createMockImage(unsigned int width,
            unsigned int height) {
        When(Method(sourceImageMock, getWidth)).Return(width);
        When(Method(sourceImageMock, getHeight)).Return(height);

        return sourceImageMock.get();
    }
};

#endif
