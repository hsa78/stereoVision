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

	for (int i = 1; i < max_disparity; ++i)
	{
		if (i == 1)
			min_disparity = calculate_disparity_of_two_pixel(x, y, 1);

		int disparity = calculate_disparity_of_two_pixel(x, y, i);

		if (disparity < min_disparity && disparity != -1)
			min_disparity = disparity;
	}

	return d_pixel(x, y, min_disparity);
}


int main(int argc, char *argv[])
{
	if ( argc != 5 )
    {
        cout << "The number of arguments is wrong\n";
        return 0;
    }
    
    Mat image_1;
    Mat image_2;

    image_1 = imread( argv[1], IMREAD_GRAYSCALE);
    image_2 = imread( argv[2], IMREAD_GRAYSCALE);

    if ( !image_1.data  || !image_2.data)
    {
        cout << "image not found \n";
        return 0;
    }

    Stereo result(image_1, image_2, stoi(argv[3]), stoi(argv[4]));

    result.compute_result_pixels();

    Mat image = result.get_result();

	namedWindow("Stereo Image", WINDOW_AUTOSIZE );

    imshow("1", image);

    waitKey(0);

    return 0;
}