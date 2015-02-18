class Image {
private:
    int width;
    int height;
    int* pixels;

    inline int getPixelIndex(int x, int y) {
	return y * width + x;
    }

public:
    Image(int width, int height) {
	this->width = width;
	this->height = height;

	pixels = new int[width * height];
    }

    void setPixel(int x, int y, int color) {
	pixels[getPixelIndex(x, y)] = color;
    }

    int getPixel(int x, int y) {
	return pixels[getPixelIndex(x, y)];
    }
};
