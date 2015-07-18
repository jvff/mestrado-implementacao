#ifndef FAKE_IMAGE_MOCK_PROXY_HPP
#define FAKE_IMAGE_MOCK_PROXY_HPP

#include <memory>

#include "fakeit.hpp"

#include "FakeImage.hpp"

using namespace fakeit;

template <typename PixelType>
class FakeImageMockProxy {
private:
    using FakeImageType = FakeImage<PixelType>;

    std::unique_ptr<Mock<FakeImageType> > mock;
    FakeImage<PixelType>& instance;

public:
    FakeImageMockProxy(unsigned int width, unsigned int height)
            : mock(new Mock<FakeImageType>()), instance(mock->get()) {
        setUpMock(width, height);
    }

    Mock<FakeImageType>& getMock() {
        return *mock;
    }

    unsigned int getWidth() const {
        return instance.getWidth();
    }

    unsigned int getHeight() const {
        return instance.getHeight();
    }

    void setPixel(unsigned int x, unsigned int y, PixelType pixel) {
        instance.setPixel(x, y, pixel);
    }

protected:
    void setUpMock(unsigned int width, unsigned int height) {
        auto& mock = *this->mock;

        When(Method(mock, getWidth)).AlwaysReturn(width);
        When(Method(mock, getHeight)).AlwaysReturn(height);

        When(Method(mock, setPixel).Using(Lt(width), Lt(height), _))
            .AlwaysReturn();
    }
};

#endif
