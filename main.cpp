#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(void)
{
	/*
	cv::VideoCapture capture(0);
	capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	*/

	/*
	if(!capture.isOpened()){
		return -1;
	}
	*/

	cv::Mat src_img = cv::imread("../jcjk/circle.png", 1);
	if(src_img.empty()) return -1;

	cv::Mat dst_img, work_img;
	dst_img = src_img.clone();
	cv::cvtColor(src_img, work_img, CV_BGR2GRAY);
	cv::GaussianBlur(work_img, work_img, cv::Size(11,11), 2, 2);


	std::vector<cv::Vec3f> circles;
	cv::HoughCircles(work_img, circles, CV_HOUGH_GRADIENT, 1, 50, 20, 50);

	std::vector<cv::Vec3f>::iterator it = circles.begin();
	for(; it!=circles.end(); ++it) {
		cv::Point center(cv::saturate_cast<int>((*it)[0]), cv::saturate_cast<int>((*it)[1]));
		int radius = cv::saturate_cast<int>((*it)[2]);
		cv::circle(dst_img, center, radius, cv::Scalar(0,0,255), 2);
	}
	cv::imshow("hoge", dst_img);
	while(true){
		if(cv::waitKey(32) == 27){
		cv::destroyAllWindows();
		break;
		}
	}
	return 0;
}
