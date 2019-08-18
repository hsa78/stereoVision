#include "headers.h"
#include <string>

using namespace std;
using namespace cv;


Stereo::Stereo(Mat image_1, Mat	image_2, int _max_disparity, int _w) : ssd(image_1, image_2) , w(_w), max_disparity(_max_disparity) , image_r(image_1) , image_l(image_2)
{ 

}

d_pixel Stereo::disparity(int x, int y)
{
	int min_disparity = total_cost(x, y);
	for (int i = 1; i < max_disparity; ++i)
	{
		int disparity = total_cost(x, y);
		if (disparity < min_disparity)
			min_disparity = disparity;
	}
	return d_pixel(x, y, min_disparity);
}

int Stereo::total_cost(int x, int y)
{

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

    Stereo(image_1, image_2, stoi(argv[3]), stoi(argv[4]));

	namedWindow("display image grayscale", WINDOW_AUTOSIZE );

    imshow("1", image_1);
    imshow("2", image_2);

    waitKey(0);

    return 0;
}