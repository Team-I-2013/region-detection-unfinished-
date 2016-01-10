#include "Header.h"

using namespace cv;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	

	cv::VideoCapture cap(0);

	cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	if (!cap.isOpened()) return -1;

	cv::namedWindow("Video", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
	cv::namedWindow("Processed", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);

	cv::Mat src_img, out_img, mask_img;
	cv::Mat dst_img = cv::Mat::zeros(480, 640, CV_8UC3);
	cv::Mat dst2_img = cv::Mat::zeros(480, 640, CV_8UC3);

	cv::Scalar paint(0,0,255);
	
   cap >> src_img;
   cv::imshow("Video", src_img);

	while (1) {
		Mat lab_img,img,img_Result, r_img, g_img,b_img;
		cvtColor(src_img, lab_img, CV_BGR2Lab);

		vector<Mat> planes;
		split(lab_img, planes);
		threshold(planes[2], r_img, 100, 255, THRESH_BINARY);
		img=10*planes[2]/planes[0];
		threshold(img, g_img,15, 255, THRESH_BINARY);
		img=10*planes[2]/planes[1];
		threshold(img, b_img, 15, 255., THRESH_BINARY);
		img=g_img+b_img;
		img_Result=img+r_img;

        vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		cv::findContours(img_Result, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

		int maxk = 0;
		double tmparea, maxarea = cv::contourArea(Mat(contours[0]));
		for ( size_t k = 1; k < contours.size(); k++) {
		 if ((tmparea = cv::contourArea(Mat(contours[k]))) > maxarea) {
			maxk = k; maxarea = tmparea;
		 }
		}

		cv::drawContours(dst_img, contours, maxk, paint, CV_FILLED, 8, hierarchy);
		cv::drawContours(dst2_img, contours, maxk, cv::Scalar(0,0,0), CV_FILLED, 8, hierarchy);
		
		cv::imshow("Processed", img_Result);
		
	}
	char key = ' ';
	char in_key = cv::waitKey(10);
	if (in_key != -1) key = in_key;
     switch (key) {
		case 'q':
		return 0;
	}
	return 0;
}
	
