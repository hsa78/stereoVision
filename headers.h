#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

class d_pixel
{
public:
	d_pixel(int _x, int _y, int _disparity) : x(_x), y(_y), disparity(_disparity) {};
private:
	int x;
	int y;
	int disparity;
};

class Cost
{
public:
	Cost(cv::Mat image_1, cv::Mat image_2){};
private:
	std::vector<std::vector<std::vector<int>>> ssd;
};


class Stereo
{
public:
	Stereo(cv::Mat image_1, cv::Mat image_2, int _max_disparity, int _w);
	void compute();
	int total_cost(int x, int y);
	d_pixel disparity(int x, int y);
private:
	cv::Mat image_l;
	cv::Mat image_r;
	cv::Mat result;
	Cost ssd;
	int max_disparity;
	int w;
};