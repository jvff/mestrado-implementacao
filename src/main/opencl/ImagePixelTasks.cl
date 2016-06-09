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
