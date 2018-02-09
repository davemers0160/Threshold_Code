// C++ Includes
// #include <map>
// #include <iostream>
// #include <sstream>
// #include <fstream>
// #include <string>
// #include <vector>
// #include <iomanip>
// #include <ctime>
// #include <chrono>
// #include <cmath>
// #include <climits>
// #include <algorithm>


// OPENCV Includes
#include <opencv2/core/core.hpp>           
#include <opencv2/highgui/highgui.hpp>     
#include <opencv2/imgproc/imgproc.hpp>  

#include "Threshold_Functions.h"

using namespace std;
using namespace cv;

void advancedThreshold(cv::Mat &inputImage, int threshold, int maxval, int minval)
{
	// accept only char type matrices
	//CV_Assert(inputImage.depth() == CV_8U);

	int channels = inputImage.channels();

	cv::MatIterator_<short> it, end;
	for (it = inputImage.begin<short>(), end = inputImage.end<short>(); it != end; ++it)
	{
		//*it = table[*it];
		if (*it == threshold)
		{
			*it = maxval;
		}
		else
		{
			*it = minval;
		}
	}

}	// end of advancedThreshold

// attempt to threshold the image by looking at the total energy value and reducing it to less
// than energyVal
void energyThreshold(cv::Mat inputImage, double energyVal, cv::Mat &thresholdImage, int &threshVal, int method)
{
	int idx;
	//double totalEnergy = (double)cv::sum(inputImage)[0];
	double intialEnergy = (double)cv::sum(inputImage)[0];
	double currentEnergy = 0.0;
	double result = 0.0;
	double min, max;

	cv::minMaxIdx(inputImage, &min, &max);

	switch (method)
	{
        // can be done over the entire image or image patches
        case 1:
            for (threshVal = (int)(min + 1); threshVal < max-1; ++threshVal)
            {
                // cycle from min+1 to max-1 on threshold values to find the tipping point
                // where ratio of the current energy to the initial energy is l.t. the
                // energy value threshold
                cv::threshold(inputImage, thresholdImage, threshVal, 255, THRESH_TOZERO);
                currentEnergy = (double)cv::sum(thresholdImage)[0];
                result = currentEnergy / intialEnergy;
                if (result < energyVal)
                {
                    break;
                }
            }
            cv::threshold(inputImage, thresholdImage, threshVal, 255, THRESH_BINARY);

            break;

        case 2:
            // check for the threshold value that produces a change ...
            for (threshVal = (int)(min + 1.0); threshVal < max; ++threshVal)
            {
                // cycle from min+1 to max-1 on threshold values to find the tipping point
                // where abs(1 - ratio of the current energy to the initial energy) is g.t. the
                // energy value threshold
                cv::threshold(inputImage, thresholdImage, threshVal, 255, THRESH_TOZERO);
                currentEnergy = (double)cv::sum(thresholdImage)[0];
                result = currentEnergy / intialEnergy;
                // 
                if (abs(1 - result) > energyVal)
                {
                    break;
                }

            }
            cv::threshold(inputImage, thresholdImage, threshVal, 255, THRESH_BINARY);

            //min = 0.0;
            break;
        default:
            break;

	}
	
    
	//cv::erode(thresholdImage, thresholdImage, cv::Mat(cv::Size(3, 3), CV_8UC1, cv::Scalar(1)), cv::Point(-1, -1), 1, BORDER_CONSTANT, cv::Scalar(0));
	//cv::dilate(thresholdImage, thresholdImage, cv::Mat(cv::Size(3, 3), CV_8UC1, cv::Scalar(1)), cv::Point(-1, -1), 2, BORDER_CONSTANT, cv::Scalar(0));
	//cv::erode(thresholdImage, thresholdImage, cv::Mat(cv::Size(3, 3), CV_8UC1, cv::Scalar(1)), cv::Point(-1, -1), 2, BORDER_CONSTANT, cv::Scalar(0));
	cv::dilate(thresholdImage, thresholdImage, cv::Mat(cv::Size(3, 3), CV_8UC1, cv::Scalar(1)), cv::Point(-1, -1), 1, BORDER_CONSTANT, cv::Scalar(0));

}	// end of energyThreshold





