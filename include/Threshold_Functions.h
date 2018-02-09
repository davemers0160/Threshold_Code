
#ifndef THRESHOLD_FUNCTIONS_H
#define	THRESHOLD_FUNCTIONS_H

// OPENCV Includes
#include <opencv2/core/core.hpp>           
#include <opencv2/highgui/highgui.hpp>     
#include <opencv2/imgproc/imgproc.hpp>  

void advancedThreshold(Mat &inputImage, int threshold, int maxval, int minval);
void energyThreshold(cv::Mat inputImage, double energyVal, cv::Mat &thresholdImage, int &threshVal, int method);

#endif	// end of THRESHOLD_FUNCTIONS_H
