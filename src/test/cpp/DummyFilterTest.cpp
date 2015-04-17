#include <gtest/gtest.h>

#include "Filter.hpp"
#include "Image.hpp"

struct DummyType1 {
    int value;
};

struct DummyType2 {
    int value;
};

class DummyFilter : public Filter<Image<DummyType1>, Image<DummyType2> > {
private:
    bool* destructorWasCalled;

public:
    DummyFilter() {
	destructorWasCalled = NULL;
    }

    virtual ~DummyFilter() {
	if (destructorWasCalled != NULL)
	    *destructorWasCalled = true;
    }

    void setDestructorListener(bool* destructorListener) {
	destructorWasCalled = destructorListener;
    }
};

TEST(DummyFilterTest, classIsntAbstract) {
    Filter<Image<DummyType1>, Image<DummyType2> >* filter = new DummyFilter();

    EXPECT_TRUE(filter != NULL);

    delete filter;
}

TEST(DummyFilterTest, destructorIsVirtual) {
    bool destructorWasCalled = false;
    DummyFilter* dummyFilter = new DummyFilter();
    Filter<Image<DummyType1>, Image<DummyType2> >* filter = dummyFilter;

    dummyFilter->setDestructorListener(&destructorWasCalled);

    delete filter;

    EXPECT_TRUE(destructorWasCalled);
}
