#include "headers.h"
#include <string>

using namespace std;
using namespace cv;


Stereo::Stereo(Mat image_1, Mat	image_2, int _max_disparity, int _w) : /*ssd(image_1, image_2) ,*/ 
w(_w), max_disparity(_max_disparity) , image_r(image_1) , image_l(image_2), result(image_2)
{ 

}

void Stereo::set_result_pixel(d_pixel d)
{
	result.at<uchar>(d.get_x(), d.get_y()) = d.get_disparity();
}

void Stereo::compute_result_pixels()
{
	for (int i = 0; i < result.rows; ++i)
	{
		for (int j = 0; j < result.cols; ++j)
			set_result_pixel(calculate_pixel_min_disparity(i, j));
	}
}

d_pixel Stereo::calculate_pixel_min_disparity(int x, int y)
{
	int min_disparity;

	for (int i = 0; i < max_disparity; ++i)
	{
		if (i == 0)
			min_disparity = calculate_disparity_of_two_window(x, y, 0);

		int disparity = calculate_disparity_of_two_window(x, y, i);

		if (disparity < min_disparity && disparity != -1)
			min_disparity = disparity;
	}

	return d_pixel(x, y, min_disparity);
}

int Stereo::calculate_disparity_of_two_window(int x, int y, int d)
{
    int sum = 0;
    if (x - d < 0)
        return -1;
    for (int i = -1 * w / 2; i <= w / 2; i++) {
        for (int j = -1 * w / 2; j <= w / 2; j++) {
            if (x + i - d < 0 || x + i < 0 || y + j < 0 || x + i > image_r.rows - 1 || y + j > image_r.cols - 1)
                continue;
            sum += disparity_between_two_pixels(x + i,y + j,d);
        }
    }
    return sum;
}

int Stereo::disparity_between_two_pixels(int img_left_x, int img_left_y, int d)
{
    int left_pixel_val = image_l.at<u_int8_t>(img_left_x,img_left_y);
    int right_pixel_val = image_r.at<u_int8_t>(img_left_x - d,img_left_y);
    return abs(left_pixel_val - right_pixel_val) ;
}

int main(int argc, char *argv[])
{
	if ( argc != 5 )
    {
        cout << "The number of arguments is wrong\n";
        return 0;
    }
    
    Mat image_r;
    Mat image_l;

    image_r = imread( argv[1], IMREAD_GRAYSCALE);
    image_l = imread( argv[2], IMREAD_GRAYSCALE);

    if ( !image_r.data  || !image_l.data)
    {
        cout << "image not found \n";
        return 0;
    }

    int max_disparity = stoi(argv[3]);
    int window_size = stoi(argv[4]);

    Stereo result(image_r, image_l, max_disparity, window_size);

    result.compute_result_pixels();

    Mat image = result.get_result();

	namedWindow("Stereo Image", WINDOW_AUTOSIZE );

    imshow("Stereo Image", image);

    waitKey(0);

    return 0;
}