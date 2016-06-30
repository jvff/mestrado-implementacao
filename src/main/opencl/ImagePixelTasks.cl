__kernel void setPixelForBoolPixelType(__read_write image2d_t image, uint x,
        uint y, uchar value) {
    const uchar FALSE_VALUE = 0;

    uint pixelGroupX = x >> 3;
    uint bitIndex = x & 7;

    uint bitToSet = 1 << bitIndex;
    uint bitsToKeep = ~bitToSet;

    int2 coordinate;

    coordinate.x = pixelGroupX;
    coordinate.y = y;

    uint4 channels = read_imageui(image, coordinate);

    if (value == FALSE_VALUE)
        channels.x &= bitsToKeep;
    else
        channels.x |= bitToSet;

    write_imageui(image, coordinate, channels);
}

__kernel void getPixelForBoolPixelType(__read_only image2d_t image, uint x,
        uint y, __global uchar* value) {
    const uchar FALSE_VALUE = 0;
    const uchar TRUE_VALUE = 1;

    uint pixelGroupX = x >> 3;
    uint bitIndex = x & 7;

    uint bitToCheck = 1 << bitIndex;

    int2 coordinate;

    coordinate.x = pixelGroupX;
    coordinate.y = y;

    uint4 channels = read_imageui(image, coordinate);
    uint pixelGroup = channels.x;
    uint pixelValue = pixelGroup & bitToCheck;

    if (pixelValue == FALSE_VALUE)
        *value = FALSE_VALUE;
    else
        *value = TRUE_VALUE;

}

__kernel void setPixelUsingOneChannel(__write_only image2d_t image, uint x,
        uint y, uint value) {
    int2 coordinate;
    uint4 channels;

    coordinate.x = x;
    coordinate.y = y;

    channels.x = value;

    write_imageui(image, coordinate, channels);
}

__kernel void getPixelUsingOneChannel(__read_only image2d_t image, uint x,
        uint y, __global uint* value) {
    int2 coordinate;

    coordinate.x = x;
    coordinate.y = y;

    uint4 channels = read_imageui(image, coordinate);

    *value = channels.x;
}

__kernel void setPixelUsingTwoChannels(__write_only image2d_t image, uint x,
        uint y, ulong value) {
    int2 coordinate;
    uint4 channels;

    coordinate.x = x;
    coordinate.y = y;

    channels.x = value & 0xFFFFFFFF;
    channels.y = (value >> 32) & 0xFFFFFFFF;

    write_imageui(image, coordinate, channels);
}

__kernel void getPixelUsingTwoChannels(__read_only image2d_t image, uint x,
        uint y, __global ulong* value) {
    int2 coordinate;

    coordinate.x = x;
    coordinate.y = y;

    uint4 channels = read_imageui(image, coordinate);
    ulong firstChannel = channels.x;
    ulong secondChannel = channels.y;

    *value = (firstChannel & 0xFFFFFFFF) | (secondChannel << 32);
}
