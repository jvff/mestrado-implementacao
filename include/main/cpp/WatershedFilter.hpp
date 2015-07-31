#ifndef WATERSHED_FILTER_HPP
#define WATERSHED_FILTER_HPP

#include "Filter.hpp"

template <typename SourcePixelType, typename DestinationPixelType,
        class DestinationImageType,
        class SourceImageType = Image<SourcePixelType> >
class WatershedFilter : public Filter<SourcePixelType, DestinationPixelType,
        DestinationImageType, SourceImageType> {
private:
    using ParentFilter = Filter<SourcePixelType, DestinationPixelType,
            DestinationImageType, SourceImageType>;

public:
    using ParentFilter::apply;

    void apply(const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) override {
        DestinationPixelType newestSegment = 0;

        for (auto pixel : getSortedPixels(sourceImage))
            processLevel(pixel, newestSegment, sourceImage, destinationImage);
    }

protected:
    DestinationImageType createDestinationImage(unsigned int width,
            unsigned int height) override {
        auto image = ParentFilter::createDestinationImage(width, height);

        image = [] (unsigned int, unsigned int) -> DestinationPixelType {
            return 0;
        };

        return image;
    }

private:
    DestinationPixelType apply(unsigned int, unsigned int,
            const SourceImageType&) override {
        return 1;
    }

    std::set<SourcePixelType> getSortedPixels(const SourceImageType& image) {
        unsigned int width = image.getWidth();
        unsigned int height = image.getHeight();
        std::set<SourcePixelType> pixels;

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y)
                pixels.insert(image.getPixel(x, y));
        }

        return pixels;
    }

    void processLevel(const SourcePixelType& level,
            DestinationPixelType& newestSegment,
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        bool newSegmentNeeded = erodeLevel(level, sourceImage,
                destinationImage);

        while (newSegmentNeeded) {
            createNewSegment(level, newestSegment, sourceImage,
                    destinationImage);

            newSegmentNeeded = erodeLevel(level, sourceImage, destinationImage);
        }
    }

    bool erodeLevel(const SourcePixelType& level,
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        bool levelIsIncomplete = false;
        bool newSegmentIsNeeded = true;
        unsigned int width = sourceImage.getWidth();
        unsigned int height = sourceImage.getHeight();

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y) {
                if (sourceImage.getPixel(x, y) == level
                        && destinationImage.getPixel(x, y) == 0) {
                    levelIsIncomplete = true;
                    newSegmentIsNeeded &= erodePixel(x, y, destinationImage);
                }
            }
        }

        return levelIsIncomplete && newSegmentIsNeeded;
    }

    bool erodePixel(unsigned int x, unsigned int y,
            DestinationImageType& image) {
        unsigned int maxX = image.getWidth() - 1;
        unsigned int maxY = image.getHeight() - 1;

        return (x == 0 || erodePixel(x, y, x - 1, y, image))
            && (y == 0 || erodePixel(x, y, x, y - 1, image))
            && (x == maxX || erodePixel(x, y, x + 1, y, image))
            && (y == maxY || erodePixel(x, y, x, y + 1, image));
    }

    bool erodePixel(unsigned int x, unsigned int y, unsigned int neighborX,
            unsigned int neighborY, DestinationImageType& image) {
        auto neighbor = image.getPixel(neighborX, neighborY);

        if (neighbor > 0) {
            image.setPixel(x, y, neighbor);

            return false;
        } else
            return true;
    }

    void createNewSegment(const SourcePixelType& level,
            DestinationPixelType& newestSegment,
            const SourceImageType& sourceImage,
            DestinationImageType& destinationImage) {
        unsigned int width = sourceImage.getWidth();
        unsigned int height = sourceImage.getHeight();

        for (unsigned int x = 0; x < width; ++x) {
            for (unsigned int y = 0; y < height; ++y) {
                if (sourceImage.getPixel(x, y) == level
                        && destinationImage.getPixel(x, y) == 0) {
                    createNewSegmentAt(x, y, newestSegment, destinationImage);

                    return;
                }
            }
        }
    }

    void createNewSegmentAt(unsigned int x, unsigned int y,
            DestinationPixelType& newestSegment, DestinationImageType& image) {
        image.setPixel(x, y, ++newestSegment);
    }
};

#endif
