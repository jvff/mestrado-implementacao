int4 getChannelShifts() {
    return (int4)( 48, 32, 16, 0 );
}

int4 getChannelMasks(int4 channelShifts) {
    int4 internalShifts;

    internalShifts.x = 64 - channelShifts.x;
    internalShifts.y = channelShifts.x - channelShifts.y;
    internalShifts.z = channelShifts.y - channelShifts.z;
    internalShifts.w = 0;

    int4 masks = (int4)( 1, 1, 1, 1 );

    masks <<= internalShifts;
    masks -= 1;

    return masks;
}

float4 getConversionFactors(int4 channelMasks) {
    float4 conversionFactors = convert_float4(channelMasks);

    conversionFactors = 1.0 / conversionFactors;

    return conversionFactors;
}

float4 readRgbImagePixel(__read_only image2d_t sourceImage, int2 coordinate) {
    uint4 absoluteChannels;
    float4 relativeChannels;

    int4 channelShifts = getChannelShifts();
    int4 channelMasks = getChannelMasks(channelShifts);
    float4 conversionFactors = getConversionFactors(channelMasks);

    uint4 originalChannels = read_imageui(sourceImage, coordinate);
    ulong originalValue = originalChannels.y;

    originalValue <<= 32;
    originalValue |= originalChannels.x;

    absoluteChannels.x = (originalValue >> channelShifts.x) & channelMasks.x;
    absoluteChannels.y = (originalValue >> channelShifts.y) & channelMasks.y;
    absoluteChannels.z = (originalValue >> channelShifts.z) & channelMasks.z;
    absoluteChannels.w = (originalValue >> channelShifts.w) & channelMasks.w;

    relativeChannels = convert_float4(absoluteChannels);
    relativeChannels *= conversionFactors;

    return relativeChannels;
}

void writeImagePixel(__write_only image2d_t destinationImage, int2 coordinate,
        float relativeValue) {
    ulong maxValue = 0xFFFFFFFFFFFFFFFF;
    float conversionFactor = (float)maxValue;

    float absoluteFloatValue = relativeValue * conversionFactor;
    ulong absoluteValue = convert_ulong_sat_rte(absoluteFloatValue);

    int4 absoluteChannels;

    absoluteChannels.x = absoluteValue & 0xFFFFFFFF;
    absoluteChannels.y = (absoluteValue >> 32) & 0xFFFFFFFF;

    write_imagei(destinationImage, coordinate, absoluteChannels);
}

__kernel void calculateLuminance(__read_only image2d_t sourceImage,
        __write_only image2d_t destinationImage) {
    const float4 colorFactors = (float4)( 0.2126, 0.7152, 0.0722, 0.0 );

    int2 coordinate;

    coordinate.x = get_global_id(0);
    coordinate.y = get_global_id(1);

    float4 colorChannels = readRgbImagePixel(sourceImage, coordinate);

    float luminanceValue = dot(colorChannels, colorFactors);

    luminanceValue = colorChannels.x * colorFactors.x;
    luminanceValue += colorChannels.y * colorFactors.y;
    luminanceValue += colorChannels.z * colorFactors.z;

    writeImagePixel(destinationImage, coordinate, luminanceValue);
}
