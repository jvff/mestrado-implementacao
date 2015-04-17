#include <gtest/gtest.h>

#include "Image.hpp"

#include "DummyType.hpp"

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

TEST(DummyImageTest, classIsntAbstract) {
    Image<DummyType>* image = new DummyImage(0, 0);

    EXPECT_TRUE(image != NULL);

    delete image;
}

TEST(DummyImageTest, destructorIsVirtual) {
    bool destructorWasCalled = false;
    DummyImage* dummyImage = new DummyImage(0, 0);
    Image<DummyType>* image = dummyImage;

    dummyImage->setDestructorListener(&destructorWasCalled);

    delete image;

    EXPECT_TRUE(destructorWasCalled);
}
