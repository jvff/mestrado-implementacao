__kernel void copyImage(__read_only image2d_t sourceImage,
        __write_only image2d_t destinationImage) {
    int2 coordinate;

    coordinate.x = get_global_id(0);
    coordinate.y = get_global_id(1);

    int4 channels = read_imagei(sourceImage, coordinate);

    write_imagei(destinationImage, coordinate, channels);
}
