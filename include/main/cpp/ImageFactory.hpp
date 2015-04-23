#ifndef IMAGE_FACTORY_HPP
#define IMAGE_FACTORY_HPP

template <typename ImageType>
class ImageFactory {
public:
    virtual ~ImageFactory() {
    }

    virtual ImageType* createImage(int width, int height) {
        return new ImageType(width, height);
    }
};

#endif
