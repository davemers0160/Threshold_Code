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

void advancedThreshold(cv::Mat inputImage, cv::Mat &thresholdImage, int threshold, int min_val, int max_val)
{
	// accept only single channel char type matrices
	//CV_Assert(inputImage.depth() == CV_8U);

	//int channels = inputImage.channels();

	cv::MatIterator_<unsigned char> it, end;
    cv::MatIterator_<unsigned char> thresh_it = thresholdImage.begin<unsigned char>();

	for (it = inputImage.begin<unsigned char>(), end = inputImage.end<unsigned char>(); it != end; ++it, ++thresh_it)
	{
		if (*it == threshold)
		{
			*thresh_it = max_val;
		}
		else
		{
			*thresh_it = min_val;
		}
	}

}	// end of advancedThreshold

// threshold function that will zero out everything that is not in the range [minval, maxval]
void rangedThreshold(cv::Mat inputImage, cv::Mat &thresholdImage, int min_val, int max_val)
{
    //CV_Assert(inputImage.depth() == CV_8U);

    cv::MatIterator_<unsigned char> it, end;
    cv::MatIterator_<unsigned char> thresh_it = thresholdImage.begin<unsigned char>();
    for (it = inputImage.begin<unsigned char>(), end = inputImage.end<unsigned char>(); it != end; ++it, ++thresh_it)
    {
        if (*it < min_val || *it > max_val)
        {
            *thresh_it = 0;
        }
        else
        {
            *thresh_it = *it;
        }
    }



}   // end of rangedThreshold

// attempt to threshold the image by looking at the total energy value and reducing it to less
// than energyVal
void energyThreshold(cv::Mat inputImage, double energyVal, cv::Mat &thresholdImage, int &threshVal, int method)
{
    //CV_Assert(inputImage.depth() == CV_8U);

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
	//cv::dilate(thresholdImage, thresholdImage, cv::Mat(cv::Size(3, 3), CV_8UC1, cv::Scalar(1)), cv::Point(-1, -1), 1, BORDER_CONSTANT, cv::Scalar(0));

}	// end of energyThreshold





