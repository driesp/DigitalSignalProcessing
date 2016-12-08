
#include "qdbmp.h"

/*
* Ondersteunde BMP varianten
*	- Niet gecompresseerde 32-bit (geen alfa kanaal support)
*	- Niet gecompresseerde 24-bit
*	- Niet gecompresseerde 8-bit (kleurindex nodig)
*/



typedef struct {
	double r;       // percent
	double g;       // percent
	double b;       // percent
} rgb;

typedef struct {
	double h;       // angle in degrees
	double s;       // percent
	double v;       // percent
} hsv;

hsv rgb2hsv(rgb in);

int main(int argc, char ** argv)
{

	BMP *image_in, *image_out, *output,  *h, *s, *v;

	image_in = BMP_ReadFile("lena.bmp");

	unsigned long int width, height;
	unsigned short depth;
	width = BMP_GetWidth(image_in);
	height = BMP_GetHeight(image_in);
	depth = BMP_GetDepth(image_in);

	image_out = BMP_Create(width, height, 8);
	h = BMP_Create(width, height, 8);
	s = BMP_Create(width, height, 8);
	v = BMP_Create(width, height,8);
	output = BMP_Create(width, height, 8);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			unsigned char r, g, b, val;
			BMP_GetPixelRGB(image_in, i, j, &r, &g, &b);
			val = 0.299*r + 0.587*g + 0.114*b;
			BMP_SetPixelRGB(image_in, i, j, 255 - r, 255 - g, 255 - b);
			BMP_SetPixelRGB(image_out, i, j, r, g, b);
			BMP_SetPixelIndex(image_out, i, j, val);
			rgb in;
			hsv out;
			in.r = r;
			in.g = b;
			in.b = b;

			out = rgb2hsv(in);
			BMP_SetPixelRGB(output, i, j, (UCHAR) (out.h / 360) * 255.0, (UCHAR)out.s * 255.0, (UCHAR)out.v * 255);
			BMP_SetPixelRGB(h, i, j, (out.h/360) *255, (out.h / 360) * 255, (out.h/360) *255);
			BMP_SetPixelRGB(s, i, j, out.s * 255 , out.s * 255, out.s * 255);
			BMP_SetPixelRGB(v, i, j, out.v * 255, out.v*255, out.v*255);
		}
	}

	for (int i = 0; i < 256; i++)
	{
		BMP_SetPaletteColor(image_out, i, i, i, i);
		BMP_SetPaletteColor(output, i, i, i, i);
		BMP_SetPaletteColor(h, i, i, i, i);
		BMP_SetPaletteColor(s, i, i, i, i);
		BMP_SetPaletteColor(v, i, i, i, i);
		
	}

	BMP_WriteFile(image_in, "negative.bmp");
	BMP_WriteFile(image_out, "GreyScale.bmp");
	BMP_WriteFile(h, "h.bmp");
	BMP_WriteFile(s, "s.bmp");
	BMP_WriteFile(v, "v.bmp");
	BMP_WriteFile(output, "hsv.bmp");

}

hsv rgb2hsv(rgb in)
{
	hsv         out;
	double      min, max, delta;

	min = in.r < in.g ? in.r : in.g;
	min = min  < in.b ? min : in.b;

	max = in.r > in.g ? in.r : in.g;
	max = max  > in.b ? max : in.b;

	out.v = max;                                
	delta = max - min;
	if (delta < 0.00001)
	{
		out.s = 0;
		out.h = 0; 
		return out;
	}
	if (max > 0.0) { 
		out.s = (delta / max);               
	}
	else {
		
		out.s = 0.0;
		out.h = 0;                          
		return out;
	}
	if (in.r >= max)                         
		out.h = (in.g - in.b) / delta;       
	else
		if (in.g >= max)
			out.h = 2.0 + (in.b - in.r) / delta;  
		else
			out.h = 4.0 + (in.r - in.g) / delta;  

	out.h *= 60.0;                            

	if (out.h < 0.0)
		out.h += 360.0;

	return out;
}