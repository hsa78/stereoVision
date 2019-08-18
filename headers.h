#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

class Cost
{
public:
	Cost(Mat image_1, Mat image_2);
private:
	std::vector<std::vector<std::vector<int>>> ssd;
};


class Stereo
{
public:
	Stereo(Mat image_1, Mat image_2);
	std::vector<std::vector<int>> disparity(std::vector<std::vector<std::vector<int>>> totalCost);
private:
	Cost ssd;
	Mat dest;
};