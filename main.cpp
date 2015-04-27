#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>
#include "uav_locator.hpp"

using std::cout;
using std::endl;
using cv::Mat;
using cv::imread;
using cv::Point3d;

int main(void) {
    Mat src = imread("sample.png", CV_LOAD_IMAGE_GRAYSCALE);
    height_point p = locate_uav(src);
    Point p1(0, 0);
    Point p2(3, 4);
    double to_show = calc_dist(p1, p2);
    cout << "Dist between " << p1 << " and " << p2 << " is " << to_show << endl;
    //cout << "cen_x:  " << p.x << "\ncen_y:  " << p.y << "\ntheta:  "
    //        << p.z << "\nDegree: " << rtod(p.z) << endl;
    cout << "Program is done." << endl;
    return 0;
}
