#define FALSE_VALUE 0
#define TRUE_VALUE ~FALSE_VALUE

uint getUintPixel(__read_only image2d_t image, int2 coordinate) {
    uint4 channels = read_imageui(image, coordinate);

    return channels.x;
}

void setUintPixel(__write_only image2d_t image, int2 coordinate, uint value) {
    uint4 channels = (uint4)( value, 0, 0, 0 );

    write_imageui(image, coordinate, value);
}

uint getBoolPixel(__read_only image2d_t image, int2 coordinate) {
    int x = coordinate.x;
    int groupX = x >> 3;
    int bitIndex = x & 7;

    uint bitToCheck = 1 << bitIndex;

    uint pixelGroup = getUintPixel(image, (int2)( groupX, coordinate.y ));
    uint selectedPixel = pixelGroup & bitToCheck;

    if (selectedPixel == FALSE_VALUE)
        return FALSE_VALUE;
    else
        return TRUE_VALUE;
}

uint getPixel(__read_only image2d_t image, int2 coordinate,
        bool boolPixelType) {
    if (boolPixelType)
        return getBoolPixel(image, coordinate);
    else
        return getUintPixel(image, coordinate);
}

uint4 calculateStructureCoordinates(int2 coordinate,
        __read_only image2d_t image, int structureSize) {
    int2 topLeftCorner = coordinate;
    int2 bottomRightCorner = coordinate;

    int2 displacement = (int2)( structureSize, structureSize );

    topLeftCorner -= displacement;
    bottomRightCorner += displacement;

    uint maxX = get_image_width(image) - 1;
    uint maxY = get_image_height(image) - 1;

    int2 topLeftLimit = (int2)( 0, 0 );
    int2 bottomRightLimit = (int2)( maxX, maxY );

    topLeftCorner = max(topLeftLimit, topLeftCorner);
    bottomRightCorner = min(bottomRightLimit, bottomRightCorner);

    return (uint4)( as_uint2(topLeftCorner), as_uint2(bottomRightCorner) );
}

uint dilate(int2 coordinate, __read_only image2d_t image,
        uint4 structureCoordinates, bool isPixelTypeBool) {
    uint startU = structureCoordinates.x;
    uint startV = structureCoordinates.y;
    uint endU = structureCoordinates.z;
    uint endV = structureCoordinates.w;

    uint result = getPixel(image, (int2)( startU, startV ), isPixelTypeBool);

    for (uint u = startU; u <= endU; ++u) {
        for (uint v = startV; v <= endV; ++v) {
            uint pixelValue = getPixel(image, (int2)( u, v ), isPixelTypeBool);

            result = max(pixelValue, result);
        }
    }

    return result;
}

uint erode(int2 coordinate, __read_only image2d_t image,
        uint4 structureCoordinates, bool isPixelTypeBool) {
    uint startU = structureCoordinates.x;
    uint startV = structureCoordinates.y;
    uint endU = structureCoordinates.z;
    uint endV = structureCoordinates.w;

    uint result = getPixel(image, (int2)( startU, startV ), isPixelTypeBool);

    for (uint u = startU; u <= endU; ++u) {
        for (uint v = startV; v <= endV; ++v) {
            uint pixelValue = getPixel(image, (int2)( u, v ), isPixelTypeBool);

            result = min(pixelValue, result);
        }
    }

    return result;
}

uint calculateMorphologicalGradient(__read_only image2d_t image,
        int2 coordinate, uint structureSize, bool isPixelTypeBool) {
    uint4 structureCoordinates = calculateStructureCoordinates(coordinate,
            image, structureSize);

    uint dilatedValue = dilate(coordinate, image, structureCoordinates,
            isPixelTypeBool);
    uint erodedValue = erode(coordinate, image, structureCoordinates,
            isPixelTypeBool);

    return dilatedValue - erodedValue;
}


__kernel void applyFilter(__read_only image2d_t sourceImage,
        __write_only image2d_t destinationImage, uint structureSize) {
    const bool pixelTypeIsNotBool = false;

    int2 coordinate;

    coordinate.x = get_global_id(0);
    coordinate.y = get_global_id(1);

    uint finalValue = calculateMorphologicalGradient(sourceImage, coordinate,
            structureSize, pixelTypeIsNotBool);

    setUintPixel(destinationImage, coordinate, finalValue);
}

__kernel void applyFilterToBoolImage(__read_only image2d_t sourceImage,
        __write_only image2d_t destinationImage, uint structureSize) {
    const bool pixelTypeIsBool = true;

    int2 coordinate;

    coordinate.x = get_global_id(0);
    coordinate.y = get_global_id(1);

    uint pixelInGroup = coordinate.x & 7;

    if (pixelInGroup == 0) {
        const uint pixelsPerGroup = 8;

        uint finalValues = 0;
        uint maskToSetBit = 1;
        int groupXCoordinate = coordinate.x >> 3;

        for (uint pixelIndex = 0; pixelIndex < pixelsPerGroup; ++pixelIndex) {
            uint finalPixelValue = calculateMorphologicalGradient(sourceImage,
                    coordinate, structureSize, pixelTypeIsBool);

            if (finalPixelValue == TRUE_VALUE)
                finalValues |= maskToSetBit;

            maskToSetBit <<= 1;
            ++coordinate.x;
        }

        coordinate.x = groupXCoordinate;

        setUintPixel(destinationImage, coordinate, finalValues);
    }
}
