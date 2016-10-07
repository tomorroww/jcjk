#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class ObjectDetection{
	public:
		ObjectDetection(void);
	private:
		cv::VideoCapture capture;
		BallDetection ball_detect;
};

#endif //OBJECT_HPP
