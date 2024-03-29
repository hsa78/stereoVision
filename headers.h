#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

class d_pixel
{
public:
	d_pixel(int _x, int _y, int _disparity) : x(_x), y(_y), disparity(_disparity) {}
	int get_x() {return x;}
	int get_y() {return	y;}
	int get_disparity() {return disparity;}
private:
	int x;
	int y;
	int disparity;
};


class Stereo
{
public:
	Stereo(cv::Mat image_1, cv::Mat image_2, int _max_disparity, int _w);
	cv::Mat get_result() {return result;}
	void compute();
	void set_pixel(d_pixel disparity);
	int total_cost(int x, int y, /**/int d);
	d_pixel disparity(int x, int y);
private:
	cv::Mat image_l;
	cv::Mat image_r;
	cv::Mat result;
	int max_disparity;
	int w;
};