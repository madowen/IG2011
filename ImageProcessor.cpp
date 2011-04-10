/*
 *  ImageProcessor.cpp
 *
 *  Created by Vicenc Gasco (vicenc.gasco@gmail.com) on 4/10/11.
 */

#include "ImageProcessor.h"

#define COLOR_RATIO (255.0/65535.0)

/* ERROR CODES (Base: 100)
 * 101: There is not an image loaded.
 * 102: Image values are not defined.
 * 103: Given row index is out of the image range.
 * 104: Given column index is out of the image range.
 * 102: Image energies are not defined.
 */

ImageProcessor::ImageProcessor() {
	image = NULL;
	pixelValues = NULL;
	pixelEnergies = NULL;
	pixelAccumuledEnergies = NULL;
	processed = false;
}

ImageProcessor::ImageProcessor(char * imgfile) {
	ImageProcessor();
	processed = false; // Define that the image is not processed,
	image(imgfile);    // load the image,
	processImage();    // and try to process it.
}

ImageProcessor::~ImageProcessor() {
	free(pixelValues);
	free(pixelEnergies);
	free(pixelAccumuledEnergies);
	free(image);
}

int ImageProcessor::rows() {
	return rows;
};

int ImageProcessor::cols() {
	return cols;
};

void ImageProcessor::processImage() {
	try {
		gatherSize();
		gatherPixelValues();
		gatherPixelEnergies();
		gatherPixelAccumuledEnergies();
		processed = true;
	} catch (int e)	{
		processed = false;
		cout << "An exception occurred. Exception Nr. " << e << endl;
		exit(1);
	}
}

bool ImageProcessor::isProcessed() {
	return processed;
}

double ImageProcessor::getPixelValue(int i, int j) {
	if (pixelValues == NULL) throw 102;
	
	if (i >= rows) throw 103;
	if (j >= cols) throw 104;
	
	return (*(pixelValues+i*rows+j));
}

double ImageProcessor::getPixelEnergy(int i, int j) {
	return 0.0;
}

double ImageProcessor::getPixelAccumuledEnergy(int i, int j) {
	return 0.0;
}

void ImageProcessor::gatherSize() {
	if (image == NULL) throw 101;
	
	rows = image.rows();
	cols = image.columns();
	
}

void ImageProcessor::gatherPixelValues() {
	if (image == NULL) throw 101;
	
	free(pixelValues);
	pixelValues = (double*) malloc(sizeof(double)*rows*cols);
	
	for(int i = 0; i < this.rows; i++) {
		for(int j = 0; j < cols; j++) {
			*(pixelValues+i*rows+j) = 0;
			*(pixelValues+i*rows+j) += COLOR_RATIO*(image.pixelColor(j,i)).redQuantum();
			*(pixelValues+i*rows+j) += COLOR_RATIO*(image.pixelColor(j,i)).greenQuantum();
			*(pixelValues+i*rows+j) += COLOR_RATIO*(image.pixelColor(j,i)).blueQuantum();
			*(pixelValues+i*rows+j) /= 3;
		}
	}
	
}

void ImageProcessor::gatherPixelEnergies() {
	if (image == NULL) throw 101;
	if (pixelValues == NULL) throw 102;
	
	free(pixelEnergies);
	pixelEnergies = (double*) malloc(sizeof(double)*rows*cols);
	
}

void ImageProcessor::gatherPixelAccumuledEnergies() {
	if (image == NULL) throw 101;
	if (pixelEnergies == NULL) throw 105;
	
}