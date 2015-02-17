class Image {
private:
    int color;

public:
    Image(int width, int height) {
    }

    void setPixel(int x, int y, int color) {
	this->color = color;
    }

    int getPixel(int x, int y) {
	return color;
    }
};
