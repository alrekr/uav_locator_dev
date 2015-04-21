#pragma once
#include <opencv2/core/core.hpp>
#include <stdlib.h>
#include <vector>

typedef struct point3d {
    double cen_x;
    double cen_y;
    double theta;
    double max_length;
} p3d;

extern int i, best_match;
extern cv::Mat src, in;
extern std::vector<std::vector<cv::Point> > received;
extern double lowest, match, theta;
extern std::vector<double> matches;
extern std::vector<std::vector<cv::Point> > original;
extern p3d p;
extern bool set_up_complete;

p3d locate_uav(cv::Mat);
void init_locate_uav(void);
void prepare_mat(cv::Mat&);
void erode_dilate(cv::Mat&);
std::vector<std::vector<cv::Point> > get_shapes(cv::Mat);
void get_orientation(std::vector<std::vector<cv::Point> >, int, p3d&);
void get_center(std::vector<std::vector<cv::Point> >, int, p3d&);
double rtod(double);
double dtor(double);

#define SAMPLE_IMAGE            "/home/alrekr/Pictures/UAS/hu-images/frame_223_threshold.png"

#define THRESHOLD 				60
#define THRESHOLD_MODE			1
#define BINARY_MAX 				255

#define MATCH_SHAPE_THRESHOLD   1
#define ORIGINAL_SHAPE          0

#define ERODE_ITERATIONS 		2
#define ERODE_PREP_ITERATIONS	5
#define DILATE_ITERATIONS 		2
#define EROSION_SIZE 			1

#define M_PIl					3.141592653589793238462643383279502884L /* pi */
