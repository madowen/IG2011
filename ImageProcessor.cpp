/*
 *  ImageProcessor.cpp
 *
 *  Created by Vicenc Gasco (vicenc.gasco@gmail.com) on 4/10/11.
 */
#include "ImageProcessor.h"

#define COLOR_RATIO (255.0/65535.0) 

using namespace std; 
using namespace Magick;

ImageProcessor::ImageProcessor(char * imgfile) {
	Image img(imgfile);		// Load the image,
	image = &img;			// keep a reference to it,
	
	rows = image->rows();
	cols = image->columns();
	
	pixelValues = new float [rows*cols];
	pixelEnergies = new float [rows*cols];
	pixelAccumuledEnergies = new float [rows*cols];
	
	processImage();			// and try to process it.
}

ImageProcessor::~ImageProcessor() {
	//delete [] pixelValues;
	//delete pixelEnergies;
	//delete pixelAccumuledEnergies;
}

int ImageProcessor::getRows() {
	return rows;
};

int ImageProcessor::getCols() {
	return cols;
};

void ImageProcessor::processImage() {
	gatherPixelValues();
	gatherPixelEnergies();
	gatherPixelAccumuledEnergies();
}

float ImageProcessor::getPixelValue(int i, int j) {
	if (i < 0 || j < 0 || j >= cols || i >= rows ) {
		return 0.0;
	}
	return (*(pixelValues+i*cols+j));
}

float ImageProcessor::getPixelEnergy(int i, int j) {
	if (i < 0 || j < 0 || j >= cols || i >= rows ) {
		return 0.0;
	}
	return (*(pixelEnergies+i*cols+j));
}

float ImageProcessor::getPixelAccumuledEnergy(int i, int j) {
	if (j < 0 || j >= cols) {
		return 999999; //we return a value over 255, which is the max energy, and then this energy won't be selected.
	}
	if (i < 0) {
		return 0;
	}
	return (*(pixelAccumuledEnergies+i*cols+j));
}

void ImageProcessor::gatherPixelValues() {
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			*(pixelValues+i*cols+j) = 0;
			*(pixelValues+i*cols+j) += (float)COLOR_RATIO*(image->pixelColor(j,i)).redQuantum();
			*(pixelValues+i*cols+j) += (float)COLOR_RATIO*(image->pixelColor(j,i)).greenQuantum();
			*(pixelValues+i*cols+j) += (float)COLOR_RATIO*(image->pixelColor(j,i)).blueQuantum();
			*(pixelValues+i*cols+j) /= 3.0;
		}
	}
}

void ImageProcessor::gatherPixelEnergies() {
	// Only to get process output
	float max = 0;
	// --
	
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			*(pixelEnergies+i*cols+j) = 0;
			*(pixelEnergies+i*cols+j) += fabs( (getPixelValue(i+1,j) - getPixelValue(i-1,j)) / 2.0 );
			*(pixelEnergies+i*cols+j) += fabs( (getPixelValue(i,j+1) - getPixelValue(i,j-1)) / 2.0 );
			// Only to get process output
			if (*(pixelEnergies+i*cols+j) > max) {
				max = *(pixelEnergies+i*cols+j);
			}
			// --
		}
	}
	
	// Only to get process output
	Geometry geom(cols,rows);
	Image im(geom,"white");
	float r = 65535.0/max;
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			Color col((int)r*(*(pixelEnergies+i*cols+j)),(int)r*(*(pixelEnergies+i*cols+j)),(int)r*(*(pixelEnergies+i*cols+j)));
			im.pixelColor(j, i,	col);
		}
	}
	im.write("energy.jpg");
	// --
}

void ImageProcessor::gatherPixelAccumuledEnergies() {
	// Only to get process output
	float max = 0;
	// --
	
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			*(pixelAccumuledEnergies+i*cols+j) = 0;
			*(pixelAccumuledEnergies+i*cols+j) += getPixelEnergy(i,j);
			*(pixelAccumuledEnergies+i*cols+j) += min(getPixelAccumuledEnergy(i-1,j), min(getPixelAccumuledEnergy(i-1,j+1), getPixelAccumuledEnergy(i-1,j-1)));
			// Only to get process output
			if (*(pixelAccumuledEnergies+i*cols+j) > max) {
				max = *(pixelAccumuledEnergies+i*cols+j);
			}
			// --
		}
	}
	
	// Only to get process output
	Geometry geom(cols,rows);
	Image im(geom,"white");
	float r = 65535.0/max;
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			Color col((int)r*(*(pixelAccumuledEnergies+i*cols+j)),(int)r*(*(pixelAccumuledEnergies+i*cols+j)),(int)r*(*(pixelAccumuledEnergies+i*cols+j)));
			im.pixelColor(j, i,	col);
		}
	}
	im.write("accumuled_energy.jpg");
	// --
}