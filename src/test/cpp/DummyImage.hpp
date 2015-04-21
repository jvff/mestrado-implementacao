#ifndef DUMMY_IMAGE_HPP
#define DUMMY_IMAGE_HPP

#include <cstddef>

#include "Image.hpp"

#include "DummyTypes.hpp"

class DummyImage : public Image<DummyType> {
private:
    bool* destructorWasCalled;
public:
    DummyImage(int width, int height) : Image(width, height) {
	destructorWasCalled = NULL;
    }

    ~DummyImage() {
	if (destructorWasCalled != NULL)
	    *destructorWasCalled = true;
    }

    virtual void setPixel(int x, int y, DummyType value) {
    }

    virtual DummyType getPixel(int x, int y) {
        static DummyType dummyValue = { 0 };

        return dummyValue;
    }

    void setDestructorListener(bool* destructorListener) {
	destructorWasCalled = destructorListener;
    }
};

#endif
