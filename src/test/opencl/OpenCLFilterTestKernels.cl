__kernel void labelPixelsWithCoordinateSum(__read_only image2d_t sourceImage,
        __write_only image2d_t destinationImage) {
    int2 coordinate;
    uint4 channels;

    coordinate.x = get_global_id(0);
    coordinate.y = get_global_id(1);

    channels.x = coordinate.x + coordinate.y;

    write_imageui(destinationImage, coordinate, channels);
}

__kernel void labelsPixelsInOrder(__read_only image2d_t sourceImage,
        __write_only image2d_t destinationImage, uint width) {
    int2 coordinate;
    uint4 channels;

    coordinate.x = get_global_id(0);
    coordinate.y = get_global_id(1);

    channels.x = coordinate.x + coordinate.y * width;

    write_imageui(destinationImage, coordinate, channels);
}

__kernel void labelsPixelsInOrderWithLocalId(__read_only image2d_t sourceImage,
        __write_only image2d_t destinationImage, uint width) {
    int2 coordinate;
    uint4 channels;

    coordinate.x = get_global_id(0);
    coordinate.y = get_global_id(1);

    channels.x = get_local_id(0) + get_local_id(1) * width;

    write_imageui(destinationImage, coordinate, channels);
}
