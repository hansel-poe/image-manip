
#include <iostream>
#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


//Constructors
Image::Image(const char* filename){
	if (read(filename))
		std::cout << "File Read sucessful: " << filename << std::endl;
	else
		std::cout << "File Read Failed: " << filename << std::endl;
}

Image::Image(int w, int h, int channels): w(w), h(h), numChannels(channels) {
	size = w * h * channels;
	data = new unsigned char[size];
}

Image::Image(const Image& img): Image(img.w, img.h, img.numChannels) {
	memcpy(data, img.data, size);
}

Image::~Image(){
	stbi_image_free(data);
}


//Read and Write

//REQUIRES: name of imagefile (Image must be in the same directory as project)
//EFFECTS: this now contains information of image file
bool Image::read(const char* filename) {
	data = stbi_load(filename, &w, &h, &numChannels, 0);

	if (data != NULL)
		size = w * h * numChannels;

	return data != NULL;
}

//REQUIRES: name of file to write
//EFFECTS: writes contents of this to filename.
bool Image::write(const char* filename) {
	ImageType imgType = getFileType(filename);
	int success = 0;

	switch (imgType) {
	case PNG:
		success = stbi_write_png(filename, w, h, numChannels, data, w * numChannels);
		break;
	case BMP: 
		success = stbi_write_bmp(filename, w, h, numChannels, data);
		break;
	case JPG:
		success = stbi_write_jpg(filename, w, h, numChannels, data, 100);
		break;
	case TGA:
		success = stbi_write_tga(filename, w, h, numChannels, data);
		break;
	}

	if (success == 0)
		std::cout << "File Write Failed: " <<filename <<  std::endl;
	else
		std::cout << "File Write Successful: " << filename << std::endl;
	return (success != 0);
}

//Helper functions
//REQUIRES: name of file to parse
//EFFECTS: parses filename and returns type of image
ImageType Image::getFileType(const char* filename) {
	const char* ext = strrchr(filename, '.');

	//DEFAULTS to png
	if (ext == nullptr)
		return PNG;

	if(strcmp(ext, ".png") == 0) {
		return PNG;
	}
	else if (strcmp(ext, ".jpg") == 0) {
		return JPG;
	}
	else if (strcmp(ext, ".tga") == 0) {
		return TGA;
	}
	else if (strcmp(ext, ".bmp") == 0) {
		return BMP;
	}
	else {
		return PNG;
	}
}

unsigned char Image::truncate(int value) {
	if (value > 255)
		return 255;
	else if (value < 0)
		return 0;
	else
		return value;
}


//Transformation functions 
//EFFECTS: Transforms image into grayscale by averaging red,green, and blue values
Image& Image::grayscaleAvg() {
	if (numChannels < 3) {
		std::cout << "Image is already greyscale!";
	}
	else {
		for (int i = 0; i < size; i += numChannels) {
			int gray = (data[i] + data[i + 1] + data[i + 2]) / 3;
			memset(data + i, gray, 3);
		}
	}
	return *this;
}

//EFFECTS:  Transforms image into grayscale using luminosity method, this 
// method uses weighted average which accounts for human perception
Image& Image::grayscaleLum() {
	if (numChannels < 3) {
		std::cout << "Image is already greyscale!";
	}
	else {
		for (int i = 0; i < size; i += numChannels) {
			int gray = 0.2126 * data[i] + 0.7152 * data[i + 1] + 0.0722 * data[i + 2];
			memset(data + i, gray, 3);
		}
	}
	return *this;
}

//REQUIRES: r, g, and b should be values between 0 and 1
//EFFECTS: Masks red, green and blue channels according to r, g and b.
Image& Image::colorMask(float r, float g, float b) {
	if (numChannels < 3) {
		std::cout << "Color Mask requires at least 3 channels, this image doesnt have that!";
	}
	else {
		for (int i = 0; i < size; i += numChannels) {
			data[i] *= r;
			data[i + 1] *= g;
			data[i + 2] *= b;
		}
	}
	return *this;
}

//EFFECTS: Flips the image around the y-axis
Image& Image::flipX() {
	unsigned char tmp[4];
	unsigned char* lp;
	unsigned char* rp;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w / 2; x++) {
			lp = &data[(x + y * w) * numChannels];
			rp = &data[((w - 1 - x) + y * w) * numChannels];

			memcpy(tmp, lp, numChannels);
			memcpy(lp, rp, numChannels);
			memcpy(rp, tmp, numChannels);
		} 
	}
	return *this;
}


//EFFECTS: Flips the image around the x-axis
Image& Image::flipY() {
	unsigned char tmp[4];
	unsigned char* up;
	unsigned char* bp;
	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h / 2; y++) {
			up = &data[(x + y * w) * numChannels];
			bp = &data[((h - 1 - y) * w + x) * numChannels];

			memcpy(tmp, up, numChannels);
			memcpy(up, bp, numChannels);
			memcpy(bp, tmp, numChannels);
		}
	}
	return *this;
}

//REQUIRES: cx: x coordiniate of top left of cropped Image
//			cy: y coordinate of top left of cropped Image
//			cw: width of cropped image 
//			ch: height of cropped image
//EFFECTS: crops this, if cx + cw > this.w or cy + ch > this.h,
//		then extra pixels will be uninitialized;
Image&  Image::crop(int cx, int cy, int cw, int ch) {
	unsigned char* croppedImg = new unsigned char[cw * ch * numChannels];

	
	for (int y = 0; y < ch; y++) {
		if (y + cy >= h) { break; }

		for (int x = 0; x < cw; x++) {
			if (x + cx >= w) { break; }
			memcpy(&croppedImg[(x + y * cw) * numChannels], &data[(cx + x + (cy + y) * w) * numChannels], numChannels);
		}
	}

	w = cw;
	h = ch;
	size = w * h * numChannels;

	delete[] data;
	data = croppedImg;
	croppedImg = nullptr;
	return *this;
}

//EFFECTS: Inverts colors of the image
Image& Image::invert() {
	unsigned char* px;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			px = &data[(x + y * w) * numChannels];
		
			if (numChannels < 3) {//Greysccale
				px[0] = 255 - px[0];
			}
			else {//RGB
				px[0] = 255 - px[0];
				px[1] = 255 - px[1];
				px[2] = 255 - px[2];
			}
		}
	}

	return *this;
}

//REQUIRES: brightAdjust should ideally be values from -255 to 255
//EFFECTS: Adjusts the brightness of color by brightAdjust, negative values will darken, positive values will brighten
Image& Image::  brighten(int brightAdjust) {
	unsigned char* px;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			px = &data[(x + y * w) * numChannels];

			if (numChannels < 3) {//Greysccale
				px[0] = truncate( px[0] + brightAdjust);
			}
			else {//RGB
				px[0] = truncate(px[0] + brightAdjust);
				px[1] = truncate(px[1] + brightAdjust);
				px[2] = truncate(px[2] + brightAdjust);
			}
		}
	}
	return *this;
}

//REQUIRES: contrastAdjust should be between -255 and 255
//EFFECTS: Adjusts contrast of this image, negative values decreases contrast and positive values increases contrast.
Image& Image::contrast(int contrastAdjust) {
	unsigned char* px;
	float factor = (259.0f * (contrastAdjust + 255)) / (255.0f * (259 - contrastAdjust));


	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			px = &data[(x + y * w) * numChannels];

			if (numChannels < 3) {//Greysccale
				px[0] = truncate(factor * (static_cast<float>(px[0]) - 128) + 128);
			}
			else {//RGB
				px[0] = truncate(factor * (static_cast<int>(px[0]) - 128) + 128);
				px[1] = truncate(factor * (static_cast<int>(px[1]) - 128) + 128);
				px[2] = truncate(factor * (static_cast<int>(px[2]) - 128) + 128);
			}
		}
	}
	return *this;
}
