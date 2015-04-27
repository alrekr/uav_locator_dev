#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>
#include "uav_locator.hpp"

using std::cout;
using std::cin;
using std::endl;
using cv::Mat;
using cv::imread;
using cv::Point3d;

int main(void) {
    Mat src = imread("sample.png", CV_LOAD_IMAGE_GRAYSCALE);
    height_point p = locate_uav(src);

    cout << "cen_x:    " << p.x << "\ncen_y:    " << p.y << "\ntheta:    "
            << p.orientation << "\nDegree:   " << rtod(p.orientation)
            << "\nDistance: " << p.distance << endl;

    cout << "Program is done." << endl;

    return 0;
}
