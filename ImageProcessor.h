/*
 *  ImageProcessor.h
 *
 *  Created by Vicenc Gasco (vicenc.gasco@gmail.com) on 4/10/11.
 */

class ImageProcessor {

public:
	ImageProcessor();
	ImageProcessor(char * imgfile);
	~ImageProcessor();
	int getRows();
	int getCols();
	
	void processImage();
	bool isProcessed();
	
	double getPixelValue(int, int);
	double getPixelEnergy(int, int);
	double getPixelAccumuledEnergy(int, int);
	
private:
	bool processed;
	int rows;
	int cols;
	int image;
	double * pixelValues;
	double * pixelEnergies;
	double * pixelAccumuledEnergies;
	
	void gatherSize();
	void gatherPixelValues();
	void gatherPixelEnergies();
	void gatherPixelAccumuledEnergies();
};
