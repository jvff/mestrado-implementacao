#ifndef PIXEL_TYPE_IMAGE_PATTERNS_HPP
#define PIXEL_TYPE_IMAGE_PATTERNS_HPP

#include <functional>
#include <initializer_list>
#include <vector>

template <typename PixelType>
class AbstractPixelTypeImagePatterns {
protected:
    using PaintFunction = std::function<
            PixelType(unsigned int, unsigned int, unsigned int, unsigned int)>;

protected:
    std::vector<PaintFunction> patterns;

protected:
    AbstractPixelTypeImagePatterns() {
    }

    AbstractPixelTypeImagePatterns(
            const std::initializer_list<PaintFunction>& patterns)
            : patterns(patterns) {
    }

public:
    unsigned int getNumberOfPatterns() {
        return patterns.size();
    }

    PaintFunction getImagePattern(unsigned int index) {
        return patterns[index];
    }
};

template <typename PixelType>
class PixelTypeImagePatterns
        : public AbstractPixelTypeImagePatterns<PixelType> {
};

template <>
class PixelTypeImagePatterns<bool>
        : public AbstractPixelTypeImagePatterns<bool> {
private:
    static bool verticalStripes(unsigned int, unsigned int, unsigned int x,
            unsigned int) {
        return ((x / 2) % 2) == 0;
    }

    static bool horizontalStripes(unsigned int, unsigned int, unsigned int,
            unsigned int y) {
        return ((y / 2) % 2) == 0;
    }

    static bool complexImage(unsigned int width, unsigned int height,
            unsigned int x, unsigned int y) {
        auto halfWidth = width / 2;
        auto halfHeight = height / 2;

        if (x < halfWidth && y < halfHeight)
            return false;
        else if (x > halfWidth && y > halfWidth)
            return true;
        else if (x < halfWidth)
            return ((x / 4) % 2) == 0;
        else
            return ((y / 4) % 2) == 0;
    }

private:
    using SuperClass = AbstractPixelTypeImagePatterns<bool>;

public:
    PixelTypeImagePatterns()
            : SuperClass({ verticalStripes, horizontalStripes, complexImage }) {
    }
};

template <>
class PixelTypeImagePatterns<int> : public AbstractPixelTypeImagePatterns<int> {
private:
    static int redGreenBlueStripes(unsigned int, unsigned int, unsigned int x,
            unsigned int y) {
        switch (y % 5) {
            case 0:
            case 1:
            case 2:
                return 0xFF << (2 * (x % 3));
            case 3:
                return 0x00000000;
            case 4:
                return 0xFFFFFFFF;
            default:
                return 0;
        };
    }

    static int uniquePixels(unsigned int width, unsigned int, unsigned int x,
            unsigned int y) {
        return x + y * width;
    }

private:
    using SuperClass = AbstractPixelTypeImagePatterns<int>;

public:
    PixelTypeImagePatterns()
            : SuperClass({ redGreenBlueStripes, uniquePixels }) {
    }
};

#endif
