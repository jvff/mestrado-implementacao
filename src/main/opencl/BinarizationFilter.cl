#define TRUE_VALUE 0xFFFFFFFF
#define FALSE_VALUE 0

__kernel void binarizeUsingGreaterThan(__read_only image2d_t sourceImage,
        __write_only image2d_t destinationImage, int threshold) {
    int2 coordinate;

    coordinate.x = get_global_id(0);
    coordinate.y = get_global_id(1);

    int4 channels = read_imagei(sourceImage, coordinate);
    int value = channels.x;

    if (value > threshold)
        value = TRUE_VALUE;
    else
        value = FALSE_VALUE;

    channels.x = value;

    write_imagei(destinationImage, coordinate, channels);
}

__kernel void binarizeUsingLessThan(__read_only image2d_t sourceImage,
        __write_only image2d_t destinationImage, int threshold) {
    int2 coordinate;

    coordinate.x = get_global_id(0);
    coordinate.y = get_global_id(1);

    int4 channels = read_imagei(sourceImage, coordinate);
    int value = channels.x;

    if (value < threshold)
        value = TRUE_VALUE;
    else
        value = FALSE_VALUE;

    channels.x = value;

    write_imagei(destinationImage, coordinate, channels);
}
