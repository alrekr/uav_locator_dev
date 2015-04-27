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

    Point p1, p2;
    cout << "Testing some ... stuff" << endl;
    cout << "X1: ";
    cin >> p1.x;
    cout << "Y1: ";
    cin >> p1.y;
    cout << "X2: ";
    cin >> p2.x;
    cout << "Y2: ";
    cin >> p2.y;

    double dist = calc_dist(p1, p2);

    cout << "Distance between " << p1 << " and " << p2 << " is " << dist << endl;

    cout << "Program is done." << endl;

    return 0;
}
