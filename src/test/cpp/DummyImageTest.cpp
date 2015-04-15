#include "Image.hpp"

struct DummyType {
    int value;
};

class DummyImage : public Image<DummyType> {
public:
    DummyImage(int width, int height) : Image(width, height) {
    }

    virtual DummyType getPixel(int x, int y) {
        static DummyType dummyValue = { 0 };

        return dummyValue;
    }
};
