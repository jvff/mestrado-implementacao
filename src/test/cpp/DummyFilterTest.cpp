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
};

TEST(DummyFilterTest, classIsntAbstract) {
    Filter<Image<DummyType1>, Image<DummyType2> >* filter = new DummyFilter();

    EXPECT_TRUE(filter != NULL);

    delete filter;
}
