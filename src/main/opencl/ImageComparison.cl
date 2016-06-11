__kernel void compareImages(__read_only image2d_t firstImage,
        __read_only image2d_t secondImage, __global uint* result) {
    int2 coordinate;
    uint4 firstPixel;
    uint4 secondPixel;

    coordinate.x = get_global_id(0);
    coordinate.y = get_global_id(1);

    firstPixel = read_imageui(firstImage, coordinate);
    secondPixel = read_imageui(secondImage, coordinate);

    if (firstPixel.x != secondPixel.x)
        *result = 1;
    else if (firstPixel.y != secondPixel.y)
        *result = 1;
}
