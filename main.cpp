#include <iostream>
#include "image.h"
using namespace std;

//NOTE: Each call to image manipulation functions changes this object, so to see each functions correctly take affect,
// Uncomment each  section of code one by one then run
 

int main() {
	//GRASYSCALE:
	Image flowers_grayAvg("flowers.jpg");
	Image flowers_grayLum("flowers.jpg");

	flowers_grayAvg.grayscaleAvg();
	flowers_grayAvg.write("gray_flowers_avg.jpg");

	flowers_grayLum.grayscaleLum();
	flowers_grayLum.write("gray_flowers_lum.jpg");
	cout << endl;


	//COLOR MASK:
	Image flowers_red("flowers.jpg");
	Image flowers_green("flowers.jpg");
	Image flowers_blue("flowers.jpg");
	Image flowers_mixed("flowers.jpg");
	Image cat_red("cat.jpg");

	flowers_red.colorMask(1, 0, 0);
	flowers_green.colorMask(0, 1, 0);
	flowers_blue.colorMask(0, 0, 1);
	flowers_mixed.colorMask(0.25, 0.33, 0.75);
	cat_red.colorMask(1, 0, 0);


	flowers_red.write("flowers_red.jpg");
	flowers_green.write("flowers_green.jpg");
	flowers_blue.write("flowers_blue.jpg");
	flowers_mixed.write("flowers_mixed.jpg");
	cat_red.write("cat_red.jpg");
	cout << endl;


	//FLIP
	Image flowers_flipX("flowers.jpg");
	Image flowers_flipY("flowers.jpg");

	flowers_flipX.flipX();
	flowers_flipY.flipY();

	flowers_flipX.write("flowers_flipX.jpg");
	flowers_flipY.write("flowers_flipY.jpg");
	cout << endl;


	//CROP
	Image flowers_crop("flowers.jpg");
	Image cat_crop("cat.jpg");

	flowers_crop.crop(300, 1000, 1000, 500);
	cat_crop.crop(200, 500, 800, 500);//overflow, there will be filler pixels;

	flowers_crop.write("flowers_crop.jpg");
	cat_crop.write("cat_crop.jpg");
	cout << endl;


	//INVERT
	Image flowers_invert("flowers.jpg");
	Image cat_invert("cat.jpg");

	flowers_invert.invert();
	cat_invert.invert();

	flowers_invert.write("flowers_invert.jpg");
	cat_invert.write("cat_invert.jpg");
	cout << endl;


	//BRIGTHEN
	Image flowers_brighten("flowers.jpg");
	Image flowers_darken("flowers.jpg");

	flowers_brighten.brighten(75);
	flowers_darken.brighten(-50);
	
	flowers_brighten.write("flowers_brighten.jpg");
	flowers_darken.write("flowers_darken.jpg");
	cout << endl;


	//Contrast
	Image flowers_contrast("flowers.jpg");
	Image flowers_uncontrast("flowers.jpg");
	Image cat_contrast("cat.jpg");
	Image cat_uncontrast("cat.jpg");

	flowers_contrast.contrast(120);
	flowers_uncontrast.contrast(-120);
	cat_contrast.contrast(255);
	cat_uncontrast.contrast(-255);//should be just gray

	flowers_contrast.write("flowers_contrast.jpg");
	flowers_uncontrast.write("flowers_uncontrast.jpg");
	cat_contrast.write("cat_contrast.jpg");
	cat_uncontrast.write("cat_uncontrast.jpg");
}
