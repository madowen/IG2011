/*
 *  ImageProcessor.h
 *
 *  Created by Vicenc Gasco (vicenc.gasco@gmail.com) on 4/10/11.
 */
#include <iostream>
#include <math.h>
#include <Magick++.h>

class ImageProcessor {

public:
	ImageProcessor(char * imgfile);
	~ImageProcessor();
	int getRows();
	int getCols();
	
	void processImage();
	
	float getPixelValue(int, int);
	float getPixelEnergy(int, int);
	float getPixelAccumuledEnergy(int, int);
	
private:
	int rows;
	int cols;
	float * pixelValues;
	float * pixelEnergies;
	float * pixelAccumuledEnergies;
	Magick::Image * image;
	
	void gatherPixelValues();
	void gatherPixelEnergies();
	void gatherPixelAccumuledEnergies();
};
