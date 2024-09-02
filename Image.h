#pragma once

//Image struct representing an image

enum ImageType {
	PNG, JPG, BMP, TGA
};

struct Image {
	unsigned char * data = NULL;
	size_t size = 0;
	int w;
	int h;
	int numChannels;

	//Constructors
	Image(const char* filename);
	Image(int w, int h, int channels);
	Image(const Image& img); 
	~Image();

	//Read and write functions
	bool read(const char* filename);
	bool write(const char* filename);

	//Helper function

	unsigned char truncate(int value);
	ImageType getFileType(const char* filename);

	//Image manipulation functions
	Image& grayscaleAvg();
	Image& grayscaleLum();
	Image& colorMask(float r, float g, float b);
	Image& flipX();
	Image& flipY();
	Image& crop(int cx, int cy, int cw, int ch);
	Image& invert();
	Image& brighten(int brightAdjust);
	Image& contrast(int contrast);
};