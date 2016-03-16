__kernel void setPixel(__write_only image2d_t image, uint x, uint y,
        uint value) {
    int2 coordinate;
    uint4 channels;

    coordinate.x = x;
    coordinate.y = y;

    channels.x = value;

    write_imageui(image, coordinate, channels);
}

__kernel void getPixel(__read_only image2d_t image, uint x, uint y,
        __global uint* value) {
    int2 coordinate;

    coordinate.x = x;
    coordinate.y = y;

    uint4 channels = read_imageui(image, coordinate);

    *value = channels.x;
}
