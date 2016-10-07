#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(void)
{
	cv::VideoCapture capture(0);
	capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	if(!capture.isOpened()){
		return -1;
	}
	while(true){
		cv::Mat frame, hoge, fuga;
		capture >> frame;
		cv::Mat gaussian, binary, temp;
		//hoge = ~frame;
		frame = cv::imread("./number.jpg");
		cv::flip(frame, hoge, 1);
		cv::cvtColor(frame, fuga, CV_BGR2GRAY);
		threshold(fuga, hoge, 0, 255, cv::THRESH_OTSU);
		cv::GaussianBlur(frame, gaussian, cv::Size(11, 11), 10, 10);
		//cv::GaussianBlur(frame, hoge, cv::Size(5, 5), 10, 10);
		//binary = gaussian;
		cv::dilate(hoge, temp, cv::Mat(), cv::Point(-1, -1), 1);
		cv::erode(temp, binary, cv::Mat(), cv::Point(-1, -1), 1);
		cv::imshow("Capture", frame);
		cv::imshow("hoge", hoge);
		cv::imshow("fuga", fuga);
		cv::imshow("Gaussian", gaussian);
		//cv::imshow("Binary", binary);
		//cv::imshow("temp", temp);
		if(cv::waitKey(30) == 27){
			cv::destroyAllWindows();
			break;
		}
	}
	return 0;
}
