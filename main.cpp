#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include "uav_locator.hpp"

using namespace std;
using namespace cv;

extern int i, best_match;
extern cv::Mat src, in;
extern std::vector<std::vector<cv::Point> > received;
extern double lowest, match, theta;
extern std::vector<double> matches;
extern std::vector<std::vector<cv::Point> > original;
extern p3d p;
extern bool set_up_complete;

int main(void) {
	//init_locate_uav();
	Mat src = imread("sample.png", CV_LOAD_IMAGE_GRAYSCALE);
	p3d p = locate_uav(src);
	cout << "\ncen_x:  " << p.cen_x << "\ncen_y:  " << p.cen_y << "\ntheta:  "
			<< p.theta << "\nDegree: " << rtod(p.theta) << endl;
	cout << "Program is done." << endl;
	return 0;
}
