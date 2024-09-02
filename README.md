# image-manip

This simple C++ Image manipulation program which takes an image input and performs a bunch of manipulation functions which alters the image. 
An Image struct stores the pixel data of an image and all the manip functions. The parsing and writing of images are made possible by stb_image and stb_image_write libraries (credit provided in the header files).

The following functions are provided:
- grayscaleAvg - turns image into grayscale by averaging the red, green and blue values
- grascaleLum - Uses the luminance method to turn an image grayscale, this method uses a weighted average which takes into account human perception
- colorMask - mask each red, green, and blue channel of the image
- flipX - flips the image around y-axis
- flipY - flips the image around x-axis
- crop - crops the image
- invert - inverts the color of the image by calculating the complement of the red, green and blue channels
- brighten - adjusts the brightness of the image
- contrast - adjusts the contrast of the image 

Note: the functions above when called on an image object, directly applies changes to that object and returns a reference of that object.
