#ifndef DUMMY_IMAGE_FACTORY_HPP
#define DUMMY_IMAGE_FACTORY_HPP

#include "ImageFactory.hpp"

#include "DummyImage.hpp"

class DummyImageFactory : public ImageFactory<DummyImage> {
private:
    bool* destructorWasCalled;

public:
    DummyImageFactory() {
	destructorWasCalled = NULL;
    }

    virtual ~DummyImageFactory() {
	if (destructorWasCalled != NULL)
	    *destructorWasCalled = true;
    }

    void setDestructorListener(bool* destructorListener) {
	destructorWasCalled = destructorListener;
    }
};

#endif
