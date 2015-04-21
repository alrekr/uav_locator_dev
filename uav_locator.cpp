#include "uav_locator.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <algorithm>

using std::cout;
using std::endl;
using std::list;
using std::vector;
using cv::Point;
using cv::Point3d;
using cv::Mat;
using cv::imread;
using cv::Size;
using cv::MORPH_ELLIPSE;
using cv::Vec4i;
using cv::Moments;

int i, best_match;
vector<vector<Point> > original, received;
double lowest = INT_MAX, match;
vector<double> matches;
Point3d _p;
bool set_up_complete = false;

Point3d locate_uav(Mat _in) {

    if (set_up_complete == false) {
        init_locate_uav();
    }

    _p.x = 0;
    _p.y = 0;
    _p.z = 4;
    received = get_shapes(_in);

    for (i = 0; i < static_cast<int>(received.size()); i++) {
        matches.push_back(matchShapes(original[ORIGINAL_SHAPE], received[i],
            CV_CONTOURS_MATCH_I1, 0));
    }

    for (i = 0; i < static_cast<int>(matches.size()); i++) {
        match = matches[i];

        if (lowest > match && match < MATCH_SHAPE_THRESHOLD) {
            lowest = match;
            best_match = i;
        }
    }

    if (lowest != INT_MAX) {
        get_orientation(received, best_match, _p);
    }

    matches.clear();
    received.clear();
    return _p;
}

/*****************************************************************************
 * Initialises some global variables
 * Input:  Mat
 * Output: None
 *****************************************************************************/
void init_locate_uav(void) {
    Mat src = imread(SAMPLE_IMAGE, CV_LOAD_IMAGE_GRAYSCALE);

    if (!src.data) {
        exit(-2);
    }

    original = get_shapes(src);
    set_up_complete = true;
}

/*****************************************************************************
 * Prepares a Mat for thresholding.
 * Input:  address to a Mat
 * Output: none
 *****************************************************************************/
void prepare_mat(Mat &_src) {
    Mat _element;
    blur(_src, _src, Size(5, 5));
    _element = getStructuringElement(MORPH_ELLIPSE,
            Size(2*EROSION_SIZE + 1, 2*EROSION_SIZE+1),
            Point(EROSION_SIZE, EROSION_SIZE));
    erode(_src, _src, _element, Point(-1, -1), ERODE_PREP_ITERATIONS);
}

/*****************************************************************************
 * Performs erosion and dilation on a Mat, to make individual contours.
 * Input:  Address to a Mat
 * Output: None
 *****************************************************************************/
void erode_dilate(Mat &_src) {
    Mat _element = getStructuringElement(MORPH_ELLIPSE,
            Size(2*EROSION_SIZE + 1, 2*EROSION_SIZE+1),
            Point(EROSION_SIZE, EROSION_SIZE));
    erode(_src, _src, _element, Point(-1, -1), ERODE_ITERATIONS);
    dilate(_src, _src, _element, Point(-1, -1), DILATE_ITERATIONS);
}

/*****************************************************************************
 * Calls prepare_mat(), threshold(), erode_dilate(), and findContours() in
 * order to find shapes in the image.
 * Input:  Mat
 * Output: cds (custom struct for storing contour and hierarchy)
 *****************************************************************************/
vector<vector<Point> > get_shapes(Mat _src) {
    vector<vector<Point> > _contours;
    vector<Vec4i> _hierarchy;

    prepare_mat(_src);
    threshold(_src, _src, THRESHOLD, BINARY_MAX, THRESHOLD_MODE);
    erode_dilate(_src);
    findContours(_src, _contours, _hierarchy, CV_RETR_TREE,
        CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    return _contours;
}

/*****************************************************************************
 * Calculates the orientation and the mass center of the found shape, based on
 * the found contours. Function is based on
 * http://stackoverflow.com/questions/14720722/binary-image-orientation
 * Input:  Found contours
 *         which contour matches with the original sample
 *         Address to object of type Point3d to hold information about contour
 * Output: None
 *****************************************************************************/
void get_orientation(vector<vector<Point> > _contours, int _n, Point3d &_p) {
    Moments _m = moments(_contours[_n], false);
    _p.x = _m.m10/_m.m00;
    _p.y = _m.m01/_m.m00;
    _p.z = 0.5 * atan2(((-2) * _m.mu11), (_m.mu20 - _m.mu02));
}

/*****************************************************************************
 * Converts radians to degree
 * Input:  double radian to convert
 * Output: double degree
 *****************************************************************************/
double rtod(double _r) {
    return _r*180/M_PIl;
}

/*****************************************************************************
 * Converts degree to radians
 * Input:  double degree to convert
 * Output: double radians
 *****************************************************************************/
double dtor(double _d) {
    return _d*M_PIl/180;
}
